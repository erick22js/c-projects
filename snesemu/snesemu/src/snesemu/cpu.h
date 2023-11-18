#ifndef SNESEMU_CPU_H
#define SNESEMU_CPU_H

#include "common.h"


/*
	CPU Global State
*/

struct{
	// Internal Registers
	uint16 reg_acu; // Acumulator A and B
	uint8 reg_dbr; // Data Bank Register
	uint16 reg_x; // Index X
	uint16 reg_y; // Index Y
	uint16 reg_dp; // Direct Page Register
	uint16 reg_s; // Stack Pointer
	uint16 reg_pc; // Program Counter
	uint8 reg_pbr; // Program Bank Register

	bool flag_e; // Emulation Flag, 0 = Native Mode
	uint8 reg_p; // Processor Status Register

	// Instructions Descriptions
	void (*proc)();
	uint16 data;
	uint32 mem_adr;
	bool is_mem_dest;
}cpu;


// Status Flags
#define CPU_FLAG_C 1 // Carry flag
#define CPU_FLAG_Z 2 // Zero flag
#define CPU_FLAG_I 4 // IRQ Disable flag
#define CPU_FLAG_D 8 // Decimal Mode flag
#define CPU_FLAG_X 16 // Index Register Select flag
#define CPU_FLAG_M 32 // Memory/Acumulator Select flag
#define CPU_FLAG_V 64 // Overflow flag
#define CPU_FLAG_N 128 // Negative flag


/*
	CPU Control Functions
*/

void cpuInit();
void cpuStep();


#endif