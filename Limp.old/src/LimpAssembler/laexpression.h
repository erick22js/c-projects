#ifndef limpasm_expression_h
#define limpasm_expression_h

#include "latokener.h"
#include "laisaenc.h"
#include "laparsemapcode.h"
#include "laparser.h"


Lbool LA_Exp_isEndOfArgument(LAToken *tk){
	return (tk->type==LATKT_EOF)||(tk->type==LATKT_NL)||LA_TK_isSymbol(tk, ',');
}

Lbool LA_Exp_isEndOfInstruction(LAToken *tk){
	return (tk->type==LATKT_EOF)||(tk->type==LATKT_NL);
}

Lbool LA_Exp_isData(LAToken *tk){
	return LA_TK_isLiteralNumeric(tk)|LA_TK_isSymbol(tk, '(')|(tk->type==LATKT_IDENTIFIER);
}


/**
	EXPRESSION RETRIEVING
*/

#define LA_NOTBINOPERATOR 0xffffffff

LAOperator LA_Exp_symbolToBinOperator(Luint32 symbol){
	switch(symbol){
		case '+':{
			return loADD;
		}
		case '-':{
			return loSUB;
		}
		case '*':{
			return loMUL;
		}
		case '/':{
			return loDIV;
		}
		case '%':{
			return loMOD;
		}
		case '&':{
			return loAND;
		}
		case '|':{
			return loOR;
		}
		case '^':{
			return loXOR;
		}
		case '>':{
			return loLSH;
		}
		case '<':{
			return loLSH;
		}
		case '=':{
			return loEQ;
		}
		case '!':{
			return loNE;
		}
	}
	return LA_NOTBINOPERATOR;
}

Luint32 LA_Exp_operatorPriority(LAOperator oprt){
	return oprt>>4;
}

void LA_Exp_fetchUnary(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val);

void LA_Exp_fetchBinary(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val, LAOperator last_oprt, LAValue *last_opr);

void LA_Exp_fetchExpression(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val);

void LA_Exp_fetchUnary(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val){
	
	LAToken tk;
	LIMPASM_Tokener_fetch(tkr, &tk);
	
	/* Retrieves operand */
	out_val->type = lsIMM32;
	out_val->identifier = FALSE;
	out_val->string = FALSE;
	
	/* A Literal Numeric */
	if(LA_TK_isLiteralNumeric(&tk)){
		out_val->data.raw = tk.data.integer;
		out_val->expression = FALSE;
	}
	/* A Identifier */
	else if(tk.type==LATKT_IDENTIFIER){
		out_val->identifier = TRUE;
		out_val->data.string = tk.data.string;
		out_val->expression = FALSE;
	}
	/* A String */
	else if(tk.type==LATKT_STRING){
		out_val->string = TRUE;
		out_val->data.string = tk.data.string;
		out_val->expression = FALSE;
	}
	/* A Symbol */
	else if(tk.type==LATKT_SYMBOL){
		
		out_val->type = lsIMM32;
		
		switch(tk.data.raw){
			case '+':{
				LA_Exp_fetchUnary(pstate, tkr, obj_map, out_val);
				if(out_val->string){
					/* TODO: error => Invalid operation with string */
					LA_THROWERR(1);
				}
			}
			break;
			case '-':{
				LAExpression exp = {0};
				LA_Exp_fetchUnary(pstate, tkr, obj_map, &exp.val1);
				if(exp.val1.string){
					/* TODO: error => Invalid operation with string */
					LA_THROWERR(1);
				}
				exp.opr = loMINUS;
				out_val->expression = TRUE;
				LA_PMC_pushObj2Map(obj_map, exp, out_val->data.pointer);
			}
			break;
			case '~':{
				LAExpression exp = {0};
				LA_Exp_fetchUnary(pstate, tkr, obj_map, &exp.val1);
				if(exp.val1.string){
					/* TODO: error => Invalid operation with string */
					LA_THROWERR(1);
				}
				exp.opr = loNOT;
				out_val->expression = TRUE;
				LA_PMC_pushObj2Map(obj_map, exp, out_val->data.pointer);
			}
			break;
			case '@':{
				LIMPASM_Tokener_previewFetch(tkr, &tk);
				if(LA_Exp_isData(&tk)){
					LAExpression exp = {0};
					LA_Exp_fetchUnary(pstate, tkr, obj_map, &exp.val1);
					if(exp.val1.string){
						/* TODO: error => Invalid operation with string */
						LA_THROWERR(1);
					}
					exp.opr = loSUB;
					exp.val2.data.integer = pstate->offset_program;
					exp.val2.type = lsIMM32;
					exp.val2.expression = FALSE;
					out_val->expression = TRUE;
					LA_PMC_pushObj2Map(obj_map, exp, out_val->data.pointer);
				}
				else{
					out_val->data.integer = pstate->offset_program;
				}
			}
			break;
			case '(':{
				LA_Exp_fetchBinary(pstate, tkr, obj_map, out_val, LA_NOTBINOPERATOR, NULL);
				
				LIMPASM_Tokener_fetch(tkr, &tk);
				if(!LA_TK_isSymbol(&tk, ')')){
					LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
				}
			}
			break;
			/* Unexpected symbol */
			default:{
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
		}
		
	}
	/* Do not match with the accepted tokens */
	else{
		LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
	}
	
}

void LA_Exp_fetchBinary(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val, LAOperator last_oprt, LAValue *last_opr){
	
	LAToken tk;
	LAExpression exp1 = {0};
	
	LAValue opr1;
	LAOperator oprt1;
	
	/* Have no any latest operation */
	if(last_oprt==LA_NOTBINOPERATOR){
		/* Retrieves first operand */
		LA_Exp_fetchUnary(pstate, tkr, obj_map, &opr1);
		
		/* Retrieves first operator sign */
		LIMPASM_Tokener_previewFetch(tkr, &tk);
		oprt1 = LA_Exp_symbolToBinOperator(tk.data.integer);
		
		/* If do not have any other operator */
		if(oprt1==LA_NOTBINOPERATOR){
			*out_val = opr1;
			return;
		}
		
		if(opr1.string){
			/* TODO: error => Invalid operation with string */
			LA_THROWERR(1);
		}
		
		LIMPASM_Tokener_fetch(tkr, &tk);
	}
	else{
		opr1 = *last_opr;
		oprt1 = last_oprt;
		if(opr1.string){
			/* TODO: error => Invalid operation with string */
			LA_THROWERR(1);
		}
	}
	
	/* Retrieves second operand */
	LAValue opr2;
	LA_Exp_fetchUnary(pstate, tkr, obj_map, &opr2);
	
	if(opr2.string){
		/* TODO: error => Invalid operation with string */
		LA_THROWERR(1);
	}
	
	/* Retrieves second operator sign */
	LIMPASM_Tokener_previewFetch(tkr, &tk);
	LAOperator oprt2 = LA_Exp_symbolToBinOperator(tk.data.integer);
	
	/* If do not have any binary operator more */
	if(oprt2==LA_NOTBINOPERATOR){
		
		exp1.val1 = opr1;
		exp1.opr = oprt1;
		exp1.val2 = opr2;
		
		out_val->expression = TRUE;
		LA_PMC_pushObj2Map(obj_map, exp1, out_val->data.pointer);
		
		return;
	}
	LIMPASM_Tokener_fetch(tkr, &tk);
	
	/* First operator must be executed at priority */
		if(LA_Exp_operatorPriority(oprt1)>=LA_Exp_operatorPriority(oprt2)){
		LAValue opr3;
		
		exp1.val1 = opr1;
		exp1.opr = oprt1;
		exp1.val2 = opr2;
		
		opr3.expression = TRUE;
		LA_PMC_pushObj2Map(obj_map, exp1, opr3.data.pointer);
		
		LA_Exp_fetchBinary(pstate, tkr, obj_map, out_val, oprt2, &opr3);
	}
	
	/* Second operator must be executed at priority */
	else{
		exp1.val1 = opr1;
		exp1.opr = oprt1;
		LA_Exp_fetchBinary(pstate, tkr, obj_map, &exp1.val2, oprt2, &opr2);
		
		out_val->expression = TRUE;
		LA_PMC_pushObj2Map(obj_map, exp1, out_val->data.pointer);
	}
	
	return;
}

void LA_Exp_fetchExpression(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAValue *out_val){
	
	LAToken tk;
	
	LA_Exp_fetchBinary(pstate, tkr, obj_map, out_val, LA_NOTBINOPERATOR, NULL);
	
	/* Default type */
	//out_val->type = lsIMM32;
	
	/* Syntax for type casting */
	LIMPASM_Tokener_previewFetch(tkr, &tk);
	
	/* Type name must follow colon symbol */
	if(LA_TK_isSymbol(&tk, ':')){
		
		LIMPASM_Tokener_fetch(tkr, &tk);
		LIMPASM_Tokener_fetch(tkr, &tk);
		
		if(LA_TK_isName(&tk, "b")){
			out_val->type = lsIMM8;
		}
		else if(LA_TK_isName(&tk, "w")){
			out_val->type = lsIMM16;
		}
		else if(LA_TK_isName(&tk, "d")){
			out_val->type = lsIMM32;
		}
		else{
			LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
		}
	}
	
}


/**
	ARGUMENTS RETRIEVING
*/

/* Fetches list of arguments for instruction */

void LA_Exp_fetchArguments(LAPState *pstate, LATokener *tkr, LADynamicArrayObjMap *obj_map, LAEntryInst *inst){
	
	LAToken tk;
	
	Luint32 ai = 0;
	
	Luint32 mad_offset = 0xff;
	Luint32 mad_length = 0xff;
	
	Luint32 scale = 0xff;
	
	for(; ai<4;){
		
		LIMPASM_Tokener_previewFetch(tkr, &tk);
		
		if(LA_Exp_isEndOfInstruction(&tk)){
			break;
		}
		
		/* Detects if the argument is a register operand */
		if(tk.type==LATKT_REGISTER){
			LIMPASM_Tokener_fetch(tkr, &tk);
			
			inst->args[ai].type = _LA_ISAREG[tk.data.icode].type;
			inst->args[ai].data.rgi = tk.data.icode;
			
		}
		/* MAD Declaration */
		else if(LA_TK_isSymbol(&tk, '[')){
			
			LIMPASM_Tokener_fetch(tkr, &tk);
			
			if(mad_offset==0xff){
				mad_offset = ai;
			}
			else{
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
			continue;
			
		}
		/* Otherwise, is a immediate expression operation */
		else{
			
			LAValue value = {0};
			
			LA_Exp_fetchExpression(pstate, tkr, obj_map, &value);
			
			LA_PMC_pushObj2Map(obj_map, value, inst->args[ai].data.value);
			inst->args[ai].type = (value.type+32);
			
		}
		
		/* Consuming the comma, break-line, EOF or special */
		LIMPASM_Tokener_fetch(tkr, &tk);
		
		/* Index scaler Declarator */
		if(LA_TK_isSymbol(&tk, '#')){
			
			LIMPASM_Tokener_fetch(tkr, &tk);
			
			/* Conditions for indexing symbol appearing */
			if((tk.type==LATKT_INTEGER)&&(scale==0xff)&&(mad_offset!=0xff)&&(mad_length==0xff)){
				
				scale = tk.data.integer;
				
				LIMPASM_Tokener_fetch(tkr, &tk);
				
			}
			else{
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
			
		}
		/* MAD End Declaration */
		if(LA_TK_isSymbol(&tk, ']')){
			
			printf("close mad declaration\n");
			
			if(mad_length==0xff){
				mad_length = ai-mad_offset+1;
			}
			else{
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
			
			if(scale==0xff){
				scale = 0;
			}
			
			/* Consuming the comma, break-line or EOF */
			LIMPASM_Tokener_fetch(tkr, &tk);
			
		}
		else{
			
			/* The closing bracket must follow the indexing term */
			if((scale!=0xff)&&(mad_length==0xff)){
				LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
			}
		}
		
		ai++;
		
		/* Must be end of argument */
		if(!LA_Exp_isEndOfArgument(&tk)){
			LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
		}
		
		/* Detected end of argument */
		if(LA_Exp_isEndOfInstruction(&tk)){
			break;
		}
		
	}
	
	/* Verify for MAD terminating */
	if((mad_length==0xff)&&(mad_length!=mad_offset)){
		LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
		/* TODO: error: expected closing bracket */
	}
	
	/* Must be end of instruction */
	if(!LA_Exp_isEndOfInstruction(&tk)){
		LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
	}
	
	inst->args_n = ai;
	inst->args_mad =  (mad_offset&0xf)|((mad_length&0xf)<<4);
	inst->arg_sc = scale;
	
}


#endif