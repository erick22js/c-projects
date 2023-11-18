#ifndef LIMP32_MMU_H_INCLUDED
#define LIMP32_MMU_H_INCLUDED

#include "cpu.h"
#include "memory.h"

/**
	MEMORY MANAGMENT UNIT COMPONENT
*/

Uint32 _l32mmu_translateDataAdr(L32Cpu *l_cpu, Uint32 adr){
	return adr;
}


#endif // LIMP32_MMU_H_INCLUDED
