#ifndef limpasm_assembler_h
#define limpasm_assembler_h

#include "lacompiler.h"


#define LIMPASM_ASM_MAXSRCFILES 16

typedef struct LAAsmb{
	
	LAParser parser;
	
	Lchar* src_file[LIMPASM_ASM_MAXSRCFILES];
	Luint32 src_n;
	
	LAWriter writer;
	Lchar* out_file;
	
}LAAsmb;


/**
	ASSEMBLY CODE COMPILING
*/

void LA_Asmb_entryInst(LAAsmb *asmb, LADynamicArrayObjMap *objs, LAEntryInst *inst){
	printf("- mni: %d\n- args_n: %d\n- args_mad: 0x%.2x\n- sc: %d\n", inst->mni, inst->args_n, inst->args_mad, inst->arg_sc);
	//printMemory(inst, sizeof(LAEntryInst), 16);
	
	LAInstruction instruction;
	
	if(inst->args_n>=4){
		LA_THROWERR(1);
	}
	
	int ai = 0;
	
	for(; ai<inst->args_n; ai++){
		int dattt = inst->args[ai].data.rgi;
		
		if((inst->args[ai].type)<32){
			instruction.a[ai].type = inst->args[ai].type;
			instruction.a[ai].data = inst->args[ai].data.rgi;
			Luint32 data = inst->args[ai].data.rgi;
		}
		else{
			LAValue *value = LA_PMC_atObjMap(objs, inst->args[ai].data.value, LAValue);
			LA_Comp_solve(&asmb->parser.state, objs, value);
			
			instruction.a[ai].type = value->type+32;
			instruction.a[ai].data = value->data.raw;
		}
	}
	
	for(; ai<3; ai++){
		instruction.a[ai].type = laVOID;
		instruction.a[ai].data = 0;
	}
	
	instruction.mni = inst->mni;
	
	instruction.mad_fmt = inst->args_mad;
	instruction.uses_sc = inst->arg_sc!=0xff;
	instruction.scale = inst->arg_sc;
	
	Luint32 buffer[4] = {0, 0, 0, 0};
	Luint32 buffer_length = 0;
	
	if(LIMPASM_IsaEnc_encode(&instruction, buffer, &buffer_length)){
		
		LIMPASM_Writer_putBuffer(&asmb->writer, (Luint8*)buffer, buffer_length);
		
	}
	else{
		LA_THROWERR(1);
	}
	
}

void LA_Asmb_entrySdat(LAAsmb *asmb, LADynamicArrayObjMap *objs, LAEntrySData *sdat){
	
	LAValue *value = LA_PMC_atObjMap(objs, sdat->value, LAValue);
	LA_Comp_solve(&asmb->parser.state, objs, value);
	
	if(value->string){
		
		Lchar* string = value->data.string;
		Luint32 index = 0;
		
		while(((*string)!=0)){
			LIMPASM_Writer_put8(&asmb->writer, *string);
			string++;
			index++;
		}
		if(sdat->aligned){
			while((index&3)!=0){
				LIMPASM_Writer_put8(&asmb->writer, 0);
				index++;
			}
		}
		
	}
	else if((sdat->aligned)||(value->type==lsIMM32)||(value->type==lsIMM)){
		LIMPASM_Writer_put32(&asmb->writer, value->data.integer);
	}
	else if(value->type==lsIMM16){
		LIMPASM_Writer_put16(&asmb->writer, value->data.integer);
	}
	else if(value->type==lsIMM8){
		LIMPASM_Writer_put8(&asmb->writer, value->data.integer);
	}
	else{
		/* -\_(•_•)_/- */
	}
	
}

void LA_Asmb_entry(LAAsmb *asmb, LAEntry *entry){
	
	LADynamicArrayObjMap *objs = &asmb->parser.objs;
	
	printf("$ENTRY$\n\tdescriptor: 0x%x\n\ttype: %d\n", entry->descriptor, entry->type);
	
	switch(entry->type){
		case leNULL:{
			
		}
		break;
		case leINST:{
			LAEntryInst *inst = LA_PMC_atObjMap(objs, entry->descriptor, LAEntryInst);
			LA_Asmb_entryInst(asmb, objs, inst);
		}
		break;
		case leSDAT:{
			LAEntrySData *sdat = LA_PMC_atObjMap(objs, entry->descriptor, LAEntrySData);
			LA_Asmb_entrySdat(asmb, objs, sdat);
		}
		default:{
			printf("<< INVALID ENTRY TYPE >>\n");
		}
	}
}

Luint32 LA_Asmb_compile(LAAsmb *asmb){
	Luint32 errcode = 0;
	
	/* Iterate Entries and solve each one */
	
	LADynamicArrayEntryMap *entries = &asmb->parser.map;
	
	if((errcode = setjmp(_LA_ERRJUMP))!=0){
		return errcode;
	}
		
	for(int ei=0; ei<entries->length; ei++){
		
		LAEntry *entry = LA_DAEntryMap_at(entries, ei);
		
		LA_Asmb_entry(asmb, entry);
		
	}
	
	return errcode;
}


/**
	ASSEMBLY CODE PARSE STAGE
*/

void LIMPASM_Asmb_init(LAAsmb *asmb, Lchar** src_file, Luint32 src_n, Lchar* out_file){
	
	for(int i=0; (i<src_n)&&(i<LIMPASM_ASM_MAXSRCFILES); i++){
		asmb->src_file[i] = src_file[i];
	}
	asmb->src_n = src_n>LIMPASM_ASM_MAXSRCFILES?LIMPASM_ASM_MAXSRCFILES:src_n;
	
	asmb->out_file = out_file;
	
}

Luint32 LA_Asmb_processSrcFile(LAAsmb *asmb, Luint32 index){
	Luint32 errcode = 0;
	
	printf("\n@\n@ PARSING: %s\n@\n\n", asmb->src_file[index]);
	LALexer *src_file = LIMPASM_Lexer_openSFile(asmb->src_file[index]);
	
	LIMPASM_Parser_swapLexer(&asmb->parser, src_file);
	errcode = LIMPASM_Parser_execute(&asmb->parser);
	LIMPASM_Lexer_close(src_file);
	
	return errcode;
}

Luint32 LIMPASM_Asmb_compile(LAAsmb *asmb){
	Luint32 errcode = 0;
	
	/* Parse Src Files */
	LIMPASM_Parser_init(&asmb->parser, NULL);
	if((errcode = LA_Asmb_processSrcFile(asmb, 0))){
		printf("\n## Parse error in file \"%s\" at line:%d and offset %d.\nCode 0x%x\n", asmb->parser.tokener.lexer->path, asmb->parser.tokener.last_tk.caret.line, asmb->parser.tokener.last_tk.caret.offset, errcode);
		return errcode;
	}
	
	/* Feedback data objs */
	printf("\n");
	printMemory(asmb->parser.map.elements, asmb->parser.map.length*sizeof(LADynamicArrayEntryMap), 16);
	printf("\n");
	
	printf("\n");
	printMemory(asmb->parser.objs.elements, asmb->parser.objs.length, 16);
	printf("\n");
	
	/* Open File Writer */
	LIMPASM_Writer_open(&asmb->writer, asmb->out_file);
	/* Binary assignature */
	/* LIMPASM_Writer_put32(&asmb->writer, 'PMIL'); */
	
	/* Compile Src Maps */
	printf("\n@\n@ COMPILING: %d src(s)\n@\n\n", asmb->src_n);
	if((errcode = LA_Asmb_compile(asmb))){
		printf("\n## Compilation error in file \"%s\" at line:%d and offset %d.\nCode 0x%x\n", asmb->parser.tokener.lexer->path, asmb->parser.tokener.last_tk.caret.line, asmb->parser.tokener.last_tk.caret.offset, errcode);
		return errcode;
	}
	
	/* Close File Writer */
	LIMPASM_Writer_close(&asmb->writer);
	
	return errcode;
}


#endif