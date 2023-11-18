#ifndef limpasm_tokener_h
#define limpasm_tokener_h

#include <string.h>

#include "lalexer.h"
#include "latokens.h"
#include "latkrdata.h"

#include "laisaenc.h"

typedef struct LATokener{
	LALexer *lexer;
	
	LAToken last_tk;
	Lbool previewed;
	
	LALinkedListStr identifiers;
	LALinkedListStr strings;
}LATokener;

Lchar* _LIMPASM_Tokener_checkForIdentifier(LATokener *tkr, Lchar* identifier){
	
	LA_LLStr_first(&tkr->identifiers);
	
	while(tkr->identifiers.actual){
		
		if(strcmp(identifier, LA_LLStr_actual(&tkr->identifiers))==0){
			return LA_LLStr_actual(&tkr->identifiers);
		}
		
		LA_LLStr_next(&tkr->identifiers);
	}
	
	return NULL;
}

Lchar* _LIMPASM_Tokener_checkForString(LATokener *tkr, Lchar* string){
	
	LA_LLStr_first(&tkr->strings);
	
	while(tkr->identifiers.actual){
		
		if(strcmp(string, LA_LLStr_actual(&tkr->strings))==0){
			return LA_LLStr_actual(&tkr->strings);
		}
		
		LA_LLStr_next(&tkr->strings);
	}
	
	return NULL;
}

Lchar* _LIMPASM_Tokener_regIdentifier(LATokener *tkr, Lchar* identifier){
	Lchar* wrap;
	if((wrap = _LIMPASM_Tokener_checkForIdentifier(tkr, identifier))){
		return wrap;
	}
	wrap = LA_TKRDATA_wrapString(identifier);
	LA_LLStr_push(&tkr->identifiers, wrap);
	return wrap;
}

Lchar* _LIMPASM_Tokener_regString(LATokener *tkr, Lchar* string){
	Lchar* wrap;
	if((wrap = _LIMPASM_Tokener_checkForString(tkr, string))){
		return wrap;
	}
	wrap = LA_TKRDATA_wrapString(string);
	LA_LLStr_push(&tkr->strings, wrap);
	return wrap;
}

void LIMPASM_Tokener_init(LATokener *tkr, LALexer *lexer){
	tkr->previewed = FALSE;
	tkr->lexer = lexer;
	LA_LLStr_init(&tkr->identifiers);
	LA_LLStr_init(&tkr->strings);
}

void _LIMPASM_Tokener_fetchNumber(LATokener *tkr, LAToken *tk, Lchar first){
	Luint32 value = 0;
	
	Luint32 chr = first;
	do{
		value *= 10;
		value += LA_TKRDATA_toNumber(chr);
		chr = LIMPASM_Lexer_get(tkr->lexer);
	}while((chr!=EOF)&&(LA_TKRDATA_ISDECIMAL(chr)));
	if(chr!=EOF){
		LIMPASM_Lexer_unget(tkr->lexer);
	}
	
	tk->type = LATKT_INTEGER;
	tk->data.integer = value;
}

void _LIMPASM_Tokener_fetchString(LATokener *tkr, LAToken *tk){
	Lchar string[512];
	Luint32 ind = 0;
	
	Luint32 chr;
	do{
		chr = LIMPASM_Lexer_get(tkr->lexer);
		string[ind] = chr;
		ind++;
	}while((chr!=EOF)&&(ind<sizeof(string)-1)&&(chr!='"'));
	ind--;
	string[ind] = 0;
	
	Lchar* regstr = _LIMPASM_Tokener_regString(tkr, string);
	
	tk->type = LATKT_STRING;
	tk->data.string = regstr;
}

void _LIMPASM_Tokener_fetchIdentifier(LATokener *tkr, LAToken *tk, Lchar first){
	Lchar identifier[32];
	Luint32 ind = 0;
	
	Luint32 chr = first;
	do{
		identifier[ind] = chr;
		ind++;
		chr = LIMPASM_Lexer_get(tkr->lexer);
	}while((chr!=EOF)&&(ind<31)&&(LA_TKRDATA_ISNAME(chr)));
	if(chr!=EOF){
		LIMPASM_Lexer_unget(tkr->lexer);
	}
	
	identifier[ind] = 0;
	
	/* Test if identifier is a reserved name */
	
	/* mnemonic */
	Luint32 mni = LIMPASM_IsaDec_toMnemonicIndex(identifier);
	if(mni!=LA_NOTOPC){
		tk->type = LATKT_MNEMONIC;
		tk->data.icode = mni;
		return;
	}
	
	/* register */
	Luint32 rgi = LIMPASM_IsaDec_toRegisterIndex(identifier);
	if(rgi!=LA_NOTREG){
		tk->type = LATKT_REGISTER;
		tk->data.icode = rgi;
		return;
	}
	
	Lchar* regident = _LIMPASM_Tokener_regIdentifier(tkr, identifier);
	
	tk->type = LATKT_IDENTIFIER;
	tk->data.string = regident;
}

void _LIMPASM_Tokener_fetch(LATokener *tkr, LAToken *tk){
	if(tkr->previewed){
		*tk = tkr->last_tk;
		tkr->previewed = FALSE;
		return;
	}
	
	Luint32 chr;
	do{
		tk->caret = tkr->lexer->caret;
		Luint32 chr = LIMPASM_Lexer_get(tkr->lexer);
		
		if(LA_TKRDATA_ISWHITE(chr)){
			continue;
		}
		else if(chr=='\n'){
			tk->type = LATKT_NL;
			tk->data.integer = 0;
		}
		else if(chr==EOF){
			tk->type = LATKT_EOF;
			tk->data.integer = 0;
		}
		else if(LA_TKRDATA_ISDECIMAL(chr)){
			_LIMPASM_Tokener_fetchNumber(tkr, tk, chr);
		}
		else if(LA_TKRDATA_ISNAME(chr)){
			_LIMPASM_Tokener_fetchIdentifier(tkr, tk, chr);
		}
		else if(chr=='"'){
			_LIMPASM_Tokener_fetchString(tkr, tk);
		}
		else{
			switch(chr){
				case ';':{
					do{
						chr = LIMPASM_Lexer_get(tkr->lexer);
					}while((chr!=EOF)&&(chr!='\n'));
					continue;
				}
				break;
				default:{
					tk->type = LATKT_SYMBOL;
					tk->data.integer = chr;
				}
			}
		}
		
		break;
	}while(chr!=EOF);
	
	tkr->last_tk = *tk;
}

void LIMPASM_Tokener_fetch(LATokener *tkr, LAToken *tk){
	_LIMPASM_Tokener_fetch(tkr, tk);
	printf("Line: %d; Offs: %d; ", (tk->caret.line), (tk->caret.offset));
	LIMPASM_TK_print(tk);
};

void LIMPASM_Tokener_previewFetch(LATokener *tkr, LAToken *tk){
	_LIMPASM_Tokener_fetch(tkr, tk);
	printf("[Preview]Line: %d; Offs: %d; ", (tk->caret.line), (tk->caret.offset));
	LIMPASM_TK_print(tk);
	tkr->previewed = TRUE;
};

void LIMPASM_Tokener_swapLexer(LATokener *tkr, LALexer *lexer){
	tkr->lexer = lexer;
}


#endif