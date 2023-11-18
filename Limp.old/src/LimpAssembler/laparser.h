#ifndef limpasm_parser_h
#define limpasm_parser_h

#include "laapi.h"
#include "lalexer.h"
#include "laparsemapcode.h"


#define LIMPASM_MAXINCLUDEFILES 32

typedef struct LAPState{
	
	/* Parse offsets */
	Luint32 offset_program;
	Luint32 offset_binary;
	Luint32 offset_entry;
	
	/* Data, defs and labels definition */
	LADictionaryV dict_label;
	LADictionaryV dict_const;
	
	/* Lexer Files include stack */
	LALexer *includes[LIMPASM_MAXINCLUDEFILES];
	Luint32 includes_i;
	
}LAPState;

Lbool LA_Parser_hasLabel(LAPState *state, Lchar* name){
	return LA_DCV_hasKey(&state->dict_label, name);
}

Lbool LA_Parser_hasConst(LAPState *state, Lchar* name){
	return LA_DCV_hasKey(&state->dict_const, name);
}

void LA_Parser_setLabel(LAPState *state, Lchar* name){
	LAValue data;
	data.type = lsIMM32;
	data.data.integer = state->offset_program;
	LA_DCV_set(&state->dict_label, name, data);
	printf("Defining label %d to \"%s\"\n", state->offset_program, name);
}

void LA_Parser_setConst(LAPState *state, Lchar* name, Luint32 value){
	LAValue data;
	data.type = lsIMM32;
	data.data.integer = value;
	LA_DCV_set(&state->dict_const, name, data);
	printf("Defining const %d to \"%s\"\n", value, name);
}

Luint32 LA_Parser_getLabel(LAPState *state, Lchar* name){
	return LA_DCV_get(&state->dict_label, name).data.integer;
}

Luint32 LA_Parser_getConst(LAPState *state, Lchar* name){
	return LA_DCV_get(&state->dict_const, name).data.integer;
}

Lbool LA_Parser_isDefinedIdentifier(LAPState *state, Lchar* identifier){
	return LA_Parser_hasLabel(state, identifier)|LA_Parser_hasConst(state, identifier);
}

Lbool LA_Parser_isDefinedValue(LAPState *state, Lchar* identifier){
	return LA_Parser_hasLabel(state, identifier)|LA_Parser_hasConst(state, identifier);
}

Luint32 LA_Parser_getDefinedValue(LAPState *state, Lchar* name){
	if(LA_Parser_hasLabel(state, name)){
		return LA_Parser_getLabel(state, name);
	}
	else if(LA_Parser_hasConst(state, name)){
		return LA_Parser_getConst(state, name);
	}
	return 0;
}


#include "laerror.h"
#include "laexpression.h"


typedef struct LAParser{
	
	LATokener tokener;
	
	LADynamicArrayEntryMap map;
	LADynamicArrayObjMap objs;
	
	LAPState state;
	
}LAParser;


void LIMPASM_Parser_swapLexer(LAParser *parser, LALexer *lexer){
	LIMPASM_Tokener_swapLexer(&parser->tokener, lexer);
}

void LIMPASM_Parser_includeFile(LAParser *parser, Lchar* path_rel){
	
	Lchar path[LIMPASM_MAXPATHSSIZE];
	LIMPASM_DIRMKR_set(path, parser->tokener.lexer->path);
	LIMPASM_DIRMKR_change(path, "../");
	LIMPASM_DIRMKR_change(path, path_rel);
	
	if(parser->state.includes_i>=LIMPASM_MAXINCLUDEFILES){
		/* TODO: error => maximum include files stack reached */
		LA_THROWERR(1);
	}
	
	LALexer *lexer = LIMPASM_Lexer_openSFile(path);
	
	if(lexer==NULL){
		/* TODO: error => src file not found */
		printf("ERROR: file at path \"%s\" not found!", path);
		LA_THROWERR(1);
	}
	
	parser->state.includes[parser->state.includes_i] = parser->tokener.lexer;
	LIMPASM_Parser_swapLexer(parser, lexer);
	parser->state.includes_i++;
}

Lbool LIMPASM_Parser_goOutIncludeFile(LAParser *parser){
	LIMPASM_Lexer_close(parser->tokener.lexer);
	if(parser->state.includes_i<=0){
		return FALSE;
	}
	parser->state.includes_i--;
	LIMPASM_Parser_swapLexer(parser, parser->state.includes[parser->state.includes_i]);
	return TRUE;
}

void LIMPASM_Parser_staticData(LAParser *parser, LAValue value, Lbool aligned){
	LAEntrySData sdat = {0};
	
	sdat.aligned = aligned;
	
	LA_PMC_pushObj2Map(&parser->objs, value, sdat.value);
	LA_PMC_pushEntry(&parser->map, &parser->objs, sdat, leSDAT);
	
	/* Calculates size of raw data */
	
	Luint32 size = 0;
	
	if(value.string){
		
		Lchar* string = value.data.string;
		
		if(aligned){
			
			while(*string){
				size++;
				string++;
			}
			while((size&3)!=0){
				size++;
			}
		}
		else{
			while(*string){
				size++;
				string++;
			}
		}
		
	}
	else if((aligned)||(value.type==lsIMM32)||(value.type==lsIMM)){
		size = 4;
	}
	else if(value.type==lsIMM16){
		size = 2;
	}
	else if(value.type==lsIMM8){
		size = 1;
	}
	
	parser->state.offset_program += size;
	parser->state.offset_binary += size;
	parser->state.offset_entry++;
	
}

void LIMPASM_Parser_init(LAParser *parser, LALexer  *src){
	
	LIMPASM_Tokener_init(&parser->tokener, src);
	
	LA_DAEntryMap_init(&parser->map);
	LA_DAObjMap_init(&parser->objs);
	
	LA_DCV_init(&parser->state.dict_label);
	LA_DCV_init(&parser->state.dict_const);
	
	parser->state.offset_program = 0;
	parser->state.offset_binary = 0;
	parser->state.offset_entry = 0;
	
	parser->state.includes_i = 0;
	
}

void _LIMPASM_Parser_process(LAParser *parser){
	
	LAToken tk;
	
	parsecycle: do{
		
		printf("## ");
		LIMPASM_Tokener_fetch(&parser->tokener, &tk);
		
		printf("## PARSING LINE %d ##\n", tk.caret.line);
		
		if(tk.type==LATKT_NL){
			goto parsecycle;
		}
		else if(tk.type==LATKT_EOF){
			break;
		}
		/* Is a detected instruction */
		else if(tk.type==LATKT_MNEMONIC){
			LAEntryInst inst = {0};
			
			LA_Exp_fetchArguments(&parser->state, &parser->tokener, &parser->objs, &inst);
			
			inst.mni = tk.data.icode;
			
			LA_PMC_pushEntry(&parser->map, &parser->objs, inst, leINST);
			
			LAInstruction instruction;
			instruction.mni = inst.mni;
			instruction.mad_fmt = inst.args_mad;
			instruction.uses_sc = inst.arg_sc!=0xff;
			instruction.a[0].type = inst.args[0].type;
			instruction.a[1].type = inst.args[1].type;
			instruction.a[2].type = inst.args[2].type;
			
			Luint32 inst_size = LIMPASM_IsaEnc_size(&instruction);
			
			/* Advances */
			parser->state.offset_program += inst_size;
			parser->state.offset_binary += inst_size;
			parser->state.offset_entry++;
			
			goto parsecycle;
		}
		else if(tk.type==LATKT_IDENTIFIER){
			
			Lchar* identifier = tk.data.string;
			
			LIMPASM_Tokener_previewFetch(&parser->tokener, &tk);
			
			/* Its a tag definition */
			if(LA_TK_isSymbol(&tk, ':')){
				/* The identifier must be not defined */
					if(LA_Parser_isDefinedIdentifier(&parser->state, identifier)){
					/* TODO: error => a symbol with same name has already been defined */
					LA_THROWERR(1);
				}
				LIMPASM_Tokener_fetch(&parser->tokener, &tk);
				LA_Parser_setLabel(&parser->state, identifier);
				goto parsecycle;
			}
			
		}
		/* Its a preprocessor directive */
		else if(LA_TK_isSymbol(&tk, '.')){
			
			LIMPASM_Tokener_fetch(&parser->tokener, &tk);
			
			/* Constant definition preprocessor */
			if(LA_TK_isName(&tk, "define")){
				LIMPASM_Tokener_fetch(&parser->tokener, &tk);
				
				/* Constant name */
				if((tk.type!=LATKT_IDENTIFIER)){
					LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
				}
				Lchar* name = tk.data.string;
				if(LA_Parser_isDefinedIdentifier(&parser->state, name)){
					/* TODO: error => a symbol with same name has already been defined */
					LA_THROWERR(1);
				}
				
				/* Constant value */
				LIMPASM_Tokener_fetch(&parser->tokener, &tk);
				Luint32 value;
				if(!LA_TK_isLiteralNumeric(&tk)){
					LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
				}
				value = tk.data.integer;
				
				/* Constant definition */
				LA_Parser_setConst(&parser->state, name, value);
				
			}
			else if(LA_TK_isName(&tk, "include")){
				LIMPASM_Tokener_fetch(&parser->tokener, &tk);
				
				/* Path String */
				if((tk.type!=LATKT_STRING)){
					LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
				}
				
				/* Import src file */
				LIMPASM_Parser_includeFile(parser, tk.data.string);
				goto parsecycle;
			}
			else if(LA_TK_isName(&tk, "data")){
				LAValue value = {0};
				
				LA_Exp_fetchExpression(&parser->state, &parser->tokener, &parser->objs, &value);
				
				LIMPASM_Parser_staticData(parser, value, TRUE);
			}
			else if(LA_TK_isName(&tk, "dat")){
				LAValue value = {0};
				
				LA_Exp_fetchExpression(&parser->state, &parser->tokener, &parser->objs, &value);
				
				LIMPASM_Parser_staticData(parser, value, FALSE);
			}
			else{
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
			
			/* Preprocessor end checker */
			LIMPASM_Tokener_fetch(&parser->tokener, &tk);
			if(!LA_Exp_isEndOfInstruction(&tk)){
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
			
		}
		else{
			LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
		}
		
	}while(tk.type!=LATKT_EOF);
	
	if(LIMPASM_Parser_goOutIncludeFile(parser)){
		goto parsecycle;
	}
	
}

Luint32 LIMPASM_Parser_execute(LAParser *parser){
	Luint32 errcode = 0;
	
	if((errcode = setjmp(_LA_ERRJUMP))!=0){
		return errcode;
	}
	
	_LIMPASM_Parser_process(parser);
	
	return 0;
}


#endif