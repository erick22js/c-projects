#include <stdio.h>
#include <stdlib.h>

#include "Limp/limp.h"
#include "interpreter.h"
#include "LimpAssembler/limpasm.h"
#include "benchmark.h"


Lchar* srcpath = "test/main.asm";
Lchar* outpath =
"#DEBUG";
//"test/main.o";

void printMemory(Luint8* buffer, Luint32 length, Luint32 collumns){
	printf("At: %p\n", buffer);
	for(Luint32 i=0; i<length;){
		printf("%p: ", buffer);
		for(Luint32 ci=0; (ci<collumns)&&(i<length); ci++){
			printf("%.2x ", buffer[ci]);
			i++;
		}
		buffer += collumns;
		printf("\n");
	}
}

#define printData(operand, collumns) printMemory(&operand, sizeof(operand), collumns)


int main(int argc, char *argv[]){
	
	LAAsmb assembler;
	LIMPASM_Asmb_init(&assembler, &srcpath, 1, outpath);
	
	if(LIMPASM_Asmb_compile(&assembler)){
		return 0;
	}
	
	
	/* Model Program */
	
	Luint32* program = _LIMPBus_g_ram;
	Luint32 program_seek = 0;
	
	program[64] = 0x9988aabb;
	
	
	/* Interpreter Script */
	
	char buffer[1024];
	
	printf("Current path: \"%s\"\n", argv[0]);
	
	for(int i=1; i<argc; i++){
		printf("== %s\n", argv[i]);
		li_execute(argv[i]);
	}
	
	_li_init();
	
	li_execute("repeat 50 step");
	
	while(_li_running){
		Luint32 bi = 0;
		char chr;
		printf("\n>> ");
		while((chr=getchar())!='\n'){
			buffer[bi] = chr;
			bi++;
		}
		buffer[bi] = 0;
		li_execute(buffer);
	}
	
	return 0;
}

