#ifndef LIMP32_CPU_MEMORY_H_INCLUDED
#define LIMP32_CPU_MEMORY_H_INCLUDED


/**
	MEMORY ACCESS BY CPU PROGRAMS
*/

Uint8 l32cpu_getMem8(L32Cpu *l_cpu, Uint32 adr);
void l32cpu_setMem8(L32Cpu *l_cpu, Uint32 adr, Uint8 data);
Uint16 l32cpu_getMem16(L32Cpu *l_cpu, Uint32 adr);
void l32cpu_setMem16(L32Cpu *l_cpu, Uint32 adr, Uint16 data);
Uint32 l32cpu_getMem32(L32Cpu *l_cpu, Uint32 adr);
void l32cpu_setMem32(L32Cpu *l_cpu, Uint32 adr, Uint32 data);


/**
	MEMORY ACCESS BY CPU PROGRAMS
*/

Uint8 l32cpu_pop8(L32Cpu *l_cpu);
void l32cpu_push8(L32Cpu *l_cpu, Uint8 data);
Uint16 l32cpu_pop16(L32Cpu *l_cpu);
void l32cpu_push16(L32Cpu *l_cpu, Uint16 data);
Uint32 l32cpu_pop32(L32Cpu *l_cpu);
void l32cpu_push32(L32Cpu *l_cpu, Uint32 data);


///Function: Access Bus memory in CPU

#define _l32cpu_getBus8(l_cpu, adr, in_data){in_data = l_cpu->devc_bus->get8(adr);}

#define _l32cpu_setBus8(l_cpu, adr, out_data){l_cpu->devc_bus->set8(adr, out_data);}

#define _l32cpu_getBus16(l_cpu, adr, in_data){in_data = l_cpu->devc_bus->get16(adr);}

#define _l32cpu_setBus16(l_cpu, adr, out_data){l_cpu->devc_bus->set16(adr, out_data);}

#define _l32cpu_getBus32(l_cpu, adr, in_data){in_data = l_cpu->devc_bus->get32(adr);}

#define _l32cpu_setBus32(l_cpu, adr, out_data){l_cpu->devc_bus->set32(adr, out_data);}

#include "cpu.h"
#include "register.h"
#include "mmu.h"

/**
	MEMORY ACCESS BY CPU PROGRAMS
*/

Uint8 l32cpu_getMem8(L32Cpu *l_cpu, Uint32 adr){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint8 data;
	_l32cpu_getBus8(l_cpu, adr, data);
	return data;
}

void l32cpu_setMem8(L32Cpu *l_cpu, Uint32 adr, Uint8 data){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus8(l_cpu, adr, data);
}

Uint16 l32cpu_getMem16(L32Cpu *l_cpu, Uint32 adr){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint16 data;
	_l32cpu_getBus16(l_cpu, adr, data);
	return data;
}

void l32cpu_setMem16(L32Cpu *l_cpu, Uint32 adr, Uint16 data){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus16(l_cpu, adr, data);
}

Uint32 l32cpu_getMem32(L32Cpu *l_cpu, Uint32 adr){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint32 data;
	_l32cpu_getBus32(l_cpu, adr, data);
	return data;
}

void l32cpu_setMem32(L32Cpu *l_cpu, Uint32 adr, Uint32 data){
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus32(l_cpu, adr, data);
}

/**
	MEMORY ACCESS BY CPU PROGRAMS
*/

Uint8 l32cpu_pop8(L32Cpu *l_cpu){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	Uint32 adr = esp_data;
	
	/// Translate the address pointed by SP and access Stack
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint8 data;
	_l32cpu_getBus8(l_cpu, adr, data);
	
	/// Updates the Stack Pointer
	esp_data += 1;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	return data;
}

void l32cpu_push8(L32Cpu *l_cpu, Uint8 data){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	
	/// Updates the Stack Pointer
	esp_data -= 1;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	/// Translate the address pointed by SP and access Stack
	Uint32 adr = esp_data;
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus8(l_cpu, adr, data);
}

Uint16 l32cpu_pop16(L32Cpu *l_cpu){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	Uint32 adr = esp_data;
	
	/// Translate the address pointed by SP and access Stack
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint16 data;
	_l32cpu_getBus16(l_cpu, adr, data);
	
	/// Updates the Stack Pointer
	esp_data += 2;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	return data;
}

void l32cpu_push16(L32Cpu *l_cpu, Uint16 data){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	
	/// Updates the Stack Pointer
	esp_data -= 2;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	/// Translate the address pointed by SP and access Stack
	Uint32 adr = esp_data;
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus16(l_cpu, adr, data);
}

Uint32 l32cpu_pop32(L32Cpu *l_cpu){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	Uint32 adr = esp_data;
	
	/// Translate the address pointed by SP and access Stack
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	Uint32 data;
	_l32cpu_getBus32(l_cpu, adr, data);
	
	/// Updates the Stack Pointer
	esp_data += 4;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	return data;
}

void l32cpu_push32(L32Cpu *l_cpu, Uint32 data){
	/// Retrieves the Stack Pointer value
	Uint32 esp_data = l32cpu_getReg_ESP(l_cpu);
	
	/// Updates the Stack Pointer
	esp_data -= 4;
	l32cpu_setReg_ESP(l_cpu, esp_data);
	
	/// Translate the address pointed by SP and access Stack
	Uint32 adr = esp_data;
	adr = _l32mmu_translateDataAdr(l_cpu, adr);
	_l32cpu_setBus32(l_cpu, adr, data);
}



#endif // LIMP32_MEMORY_H_INCLUDED
