#ifndef limpasm_compiler_h
#define limpasm_compiler_h

#include "laisaenc.h"
#include "laparser.h"
#include "lawriter.h"


void LA_Comp_solveValue(LAPState *state, LADynamicArrayObjMap *objs, LAValue *out_opr);

void LA_Comp_solveExpression(LAPState *state, LADynamicArrayObjMap *objs, LAExpression *exp, LAValue *out_opr);

void LA_Comp_solveValue(LAPState *state, LADynamicArrayObjMap *objs, LAValue *out_opr){
	if(out_opr->expression){
		LAExpression *exp1 = LA_PMC_atObjMap(objs, out_opr->data.pointer, LAExpression);
		LA_Comp_solveExpression(state, objs, exp1, out_opr);
	}
	else if(out_opr->identifier){
		printf("Olo\n");
		if(LA_Parser_isDefinedValue(state, out_opr->data.string)){
			out_opr->data.integer = LA_Parser_getDefinedValue(state, out_opr->data.string);
		}
		else{
			printf("name \"%s\" is not defined\n", out_opr->data.string);
			/* TODO: error => has no any symbol with this name defined */
			LA_THROWERR(1);
		}
	}
	printf("??? VALUE\n\ttype: 0x%x\n\tdata: 0x%x\n\tis_exp: 0x%x\n\tis_ident: %d\n", out_opr->type, out_opr->data.raw, out_opr->expression, out_opr->identifier);
	printMemory(out_opr, sizeof(LAValue), 16);
	printf("\n");
}

void LA_Comp_solveExpression(LAPState *state, LADynamicArrayObjMap *objs, LAExpression *exp, LAValue *out_opr){
	LA_Comp_solveValue(state, objs, &exp->val1);
	
	/* Unary operation */
	switch(exp->opr){
		case loMINUS:{
			out_opr->data.integer = -((Lsint32)exp->val1.data.integer);
		}
		break;
		
		/* Binary operation */
		default:{
			
			LA_Comp_solveValue(state, objs, &exp->val2);
			
			switch(exp->opr){
				case loADD:{
					out_opr->data.integer = exp->val1.data.integer+exp->val2.data.integer;
				}
				break;
				case loSUB:{
					out_opr->data.integer = exp->val1.data.integer-exp->val2.data.integer;
				}
				break;
				case loMUL:{
					out_opr->data.integer = exp->val1.data.integer*exp->val2.data.integer;
				}
				break;
				case loDIV:{
					out_opr->data.integer = exp->val1.data.integer/exp->val2.data.integer;
				}
				break;
				case loMOD:{
					out_opr->data.integer = exp->val1.data.integer%exp->val2.data.integer;
				}
				break;
				case loAND:{
					out_opr->data.integer = exp->val1.data.integer&exp->val2.data.integer;
				}
				break;
				case loOR:{
					out_opr->data.integer = exp->val1.data.integer|exp->val2.data.integer;
				}
				break;
				case loXOR:{
					out_opr->data.integer = exp->val1.data.integer^exp->val2.data.integer;
				}
				break;
				case loLSH:{
					out_opr->data.integer = exp->val1.data.integer<<exp->val2.data.integer;
				}
				break;
				case loRSH:{
					out_opr->data.integer = exp->val1.data.integer>>exp->val2.data.integer;
				}
				break;
				case loEQ:{
					out_opr->data.integer = exp->val1.data.integer==exp->val2.data.integer;
				}
				break;
				case loNE:{
					out_opr->data.integer = exp->val1.data.integer!=exp->val2.data.integer;
				}
				break;
				default:{
					LA_THROWERR(LAERR_UNEXPECTEDTOKEN);
				}
			}
			
		}
	}
	
	printf("??? EXPRESSION\n\toperator: 0x%x\n", exp->opr);
	printf("\tVALUE1\n\t\ttype: 0x%x\n\t\tdata: 0x%x\n\t\tis_exp: 0x%x\n\t\tis_ident: %d\n", exp->val1.type, exp->val1.data.raw, exp->val1.expression, exp->val1.identifier);
	printf("\tVALUE2\n\t\ttype: 0x%x\n\t\tdata: 0x%x\n\t\tis_exp: 0x%x\n\t\tis_ident: %d\n", exp->val2.type, exp->val2.data.raw, exp->val2.expression, exp->val2.identifier);
	printMemory(exp, sizeof(LAExpression), 16);
	printf("\n");
}

void LA_Comp_solve(LAPState *state, LADynamicArrayObjMap *objs, LAValue *opr){
	LA_Comp_solveValue(state, objs, opr);
}



#endif