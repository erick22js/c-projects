#ifndef limpasm_tokens_h
#define limpasm_tokens_h

#include <stdio.h>
#include "lalexer.h"


typedef union LATokenData LATokenData;

typedef struct LAToken{
	Luint32 type;
	union LATokenData{
		Luint32 raw;
		Luint32 icode;
		Luint32 integer;
		Lfloat32 flp;
		Lchar* string;
		void *pointer;
	}data;
	LACaret caret;
}LAToken;

#define LATKT_EOF 0xffffffff
#define LATKT_NL 0xff
#define LATKT_INTEGER 0x00
#define LATKT_FLOAT 0x01
#define LATKT_STRING 0x02
#define LATKT_IDENTIFIER 0x10
#define LATKT_MNEMONIC 0x11
#define LATKT_REGISTER 0x12
#define LATKT_SYMBOL 0x80

Lbool LA_TK_isLiteralNumeric(LAToken *tk){
	return (tk->type==LATKT_INTEGER)||(tk->type==LATKT_FLOAT);
}

Lbool LA_TK_isSymbol(LAToken *tk, Lchar symbol){
	return (tk->type==LATKT_SYMBOL)&&(tk->data.integer==symbol);
}

Lbool LA_TK_isString(LAToken *tk, Lchar* string){
	return (tk->type==LATKT_STRING)&&(tk->data.string==string);
}

Lbool LA_TK_isIdentifier(LAToken *tk, Lchar* identifier){
	return (tk->type==LATKT_IDENTIFIER)&&(tk->data.string==identifier);
}

Lbool LA_TK_isName(LAToken *tk, Lchar* name){
	if(tk->type==LATKT_IDENTIFIER){
		return (strcmp(tk->data.string, name)==0);
	}
	return FALSE;
}

void LIMPASM_TK_print(LAToken *tk){
	
	printf("TOKEN# ");
	
	switch(tk->type){
		case LATKT_EOF:{
			printf("EOF");
		}
		break;
		case LATKT_NL:{
			printf("NEW LINE");
		}
		break;
		case LATKT_INTEGER:{
			printf("Int: %d", tk->data.integer);
		}
		break;
		case LATKT_FLOAT:{
			printf("Float: %f", tk->data.flp);
		}
		break;
		case LATKT_SYMBOL:{
			printf("Symbol: %c [0x%x]", tk->data.integer, tk->data.integer);
		}
		break;
		case LATKT_STRING:{
			printf("String: \"%s\"", tk->data.string);
		}
		break;
		case LATKT_IDENTIFIER:{
			printf("Identifier: %s", tk->data.string);
		}
		break;
		case LATKT_MNEMONIC:{
			printf("MNE [%d]", tk->data.icode);
		}
		break;
		case LATKT_REGISTER:{
			printf("REG [%d]", tk->data.icode);
		}
		break;
		default:{
			printf("- unknown -");
		}
	}
	
	printf("\n");
	
}



#endif