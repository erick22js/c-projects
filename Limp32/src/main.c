#include "test.h"

int main(){
	
	L32AppJmp jump;
	
	const Uint32 code = l32app_jmp_set(&jump);
	
	printf("Hello World!\n");
	
	l32app_jmp_jmp(&jump, 0);
	
	
	
	test_initialize();
	
	l32cpu_setMem8(cpu, 4, 0x48aa32bb);
	
	l32cpu_togFlag_CF(cpu);
	
	//printf("Valor %x\n", l32cpu_getMem8(cpu, 4));
	printf("Flag pg %x\n", l32cpu_getFlag_CF(cpu));
	printf("\n\nEnd of program!");
	return 0;
}
