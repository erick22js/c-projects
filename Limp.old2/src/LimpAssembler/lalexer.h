#ifndef limpasm_lexer_h
#define limpasm_lexer_h

#include "lafile.h"
#include "ladirmkr.h"

#define LIMPASM_MAXLEXERS LIMPASM_FILESMAX


typedef struct LACaret{
	Luint32 index; /* Position inside file */
	Luint32 line; /* Line actual index */
	Luint32 offset; /* Offset in current line */
}LACaret;

struct LALexer{
	
	Lbool open;
	LAFile file;
	
	Lchar path[LIMPASM_MAXPATHSSIZE];
	
	LACaret caret;
	
	Luint32 lcbuff[32]; /* Last fetched characters */
	Luint32 lcbuff_i; /* Last fetched index */
	
}_LALexers[LIMPASM_MAXLEXERS];

typedef struct LALexer LALexer;


LALexer *LIMPASM_Lexer_openSFile(Lchar* path){
	for(Luint32 lli=1; lli<LIMPASM_MAXLEXERS; lli++){
		if(!_LALexers[lli].open){
			LAFile file = LIMPASM_File_openSFile(path, LAFILE_R);
			if(file==(LAFile)NULL){
				return NULL;
			}
			LIMPASM_DIRMKR_set(_LALexers[lli].path, path);
			_LALexers[lli].file = file;
			_LALexers[lli].open = TRUE;
			_LALexers[lli].caret.index = 0;
			_LALexers[lli].caret.line = 1;
			_LALexers[lli].caret.offset = 1;
			_LALexers[lli].lcbuff_i = 0;
			return &_LALexers[lli];
		}
	}
	return NULL;
}

LALexer *LIMPASM_Lexer_openBuffer(Luint8* buffer, Luint32 length){
	for(Luint32 lli=1; lli<LIMPASM_MAXLEXERS; lli++){
		if(!_LALexers[lli].open){
			LAFile file = LIMPASM_File_openBuffer(buffer, length, LAFILE_R);
			if(file==(LAFile)NULL){
				continue;
			}
			LIMPASM_DIRMKR_set(_LALexers[lli].path, "Buffer");
			_LALexers[lli].file = file;
			_LALexers[lli].open = TRUE;
			_LALexers[lli].caret.index = 0;
			_LALexers[lli].caret.line = 1;
			_LALexers[lli].caret.offset = 1;
			_LALexers[lli].lcbuff_i = 0;
			return &_LALexers[lli];
		}
	}
	return NULL;
}

void LIMPASM_Lexer_close(LALexer *lexer){
	LIMPASM_File_close(lexer->file);
	lexer->open = FALSE;
}

Luint32 __LIMPASM_Lexer_get(LALexer *lexer){
	Luint32 chr;
	chr = LIMPASM_File_getc(lexer->file);
	lexer->lcbuff[lexer->lcbuff_i&0x1f] = chr;
	lexer->lcbuff_i++;
	return chr;
}

Luint32 _LIMPASM_Lexer_get(LALexer *lexer){
	Luint32 chr;
	chr = __LIMPASM_Lexer_get(lexer);
	
	if(chr=='\n'){
		lexer->caret.line++;
		lexer->caret.offset = 0;
	}
	lexer->caret.offset++;
	lexer->caret.index++;
	
	if(chr==0){
		return EOF;
	}
	
	return chr;
}

Luint32 LIMPASM_Lexer_get(LALexer *lexer){
	Luint32 chr = _LIMPASM_Lexer_get(lexer);
	//printf("chr: '%c'[%d]\n", chr, chr);
	return chr;
}

Luint32 __LIMPASM_Lexer_unget(LALexer *lexer){
	Luint32 chr;
	LIMPASM_File_ungetc(lexer->file);
	lexer->lcbuff_i++;
	chr = lexer->lcbuff[lexer->lcbuff_i&0x1f];
	return chr;
}

Luint32 _LIMPASM_Lexer_unget(LALexer *lexer){
	Luint32 chr;
	
	chr = __LIMPASM_Lexer_unget(lexer);
	
	if(chr=='\n'){
		lexer->caret.line--;
		lexer->caret.offset = 0xffff;
	}
	lexer->caret.offset--;
	lexer->caret.index--;
	
	if(chr==0){
		return EOF;
	}
	return chr;
}

Luint32 LIMPASM_Lexer_unget(LALexer *lexer){
	Luint32 chr = _LIMPASM_Lexer_unget(lexer);
	return chr;
}





#endif
