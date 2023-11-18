#ifndef snemus_cpu_h
#define snemus_cpu_h

typedef struct SMCpu SMCpu;

#define SMCPU_STATUS_ACU16BIT (!(m_cpu->flag_e||getBit(m_cpu->reg_psr, SM_FLAG_M)))
#define SMCPU_STATUS_MEMORY16BIT (!(m_cpu->flag_e||getBit(m_cpu->reg_psr, SM_FLAG_M)))
#define SMCPU_STATUS_INDEX16BIT (!(m_cpu->flag_e||getBit(m_cpu->reg_psr, SM_FLAG_X)))
#define SMCPU_STATUS_NATIVE16BIT (!(m_cpu->flag_e))

#include "../api.h"
#include "../bus.h"
#include "instruction.h"
#include "../emu.h"


struct SMCpu{
	
	/* Registers */
	
	Uint16 reg_acu;
	Uint8 reg_dbr;
	Uint16 reg_x;
	Uint16 reg_y;
	Uint16 reg_dp;
	Uint16 reg_sp;
	Uint16 reg_pc; Uint8 reg_pbr;
	Uint32 reg_lpc;
	
	Bool flag_e; /* Emulation */
	Uint8 reg_psr; /* Processor Status Register */
	
	
	/* Instruction Operators */
	
	SMInstruction *instruction;
	
	SMAdrmMod arg_mod; /* Addressing Mode must retrieve data from memory */
	Uint8 arg_fetchedI; /* Fetched Instruction */
	Uint32 arg_data;
	Uint32 arg_effectiveAdr;
	Bool arg_pcCrossBoundary;
	
	
	/* Control and Properties */
	Bool waiting;
	Uint32 cycles_count;
	
	
	/* Ports and Wiring */
	SMBus *io_bus;
	SMEmulator *emulator;
	
};


typedef struct SMIntType{
	const Uint16 emulation, native;
}SMIntType;

extern const SMIntType SM_INT_IRQ;
extern const SMIntType SM_INT_RESET;
extern const SMIntType SM_INT_NMI;
extern const SMIntType SM_INT_ABORT;
extern const SMIntType SM_INT_BRK;
extern const SMIntType SM_INT_COP;

#define SM_FLAG_C 0 /* Carry */
#define SM_FLAG_Z 1 /* Zero */
#define SM_FLAG_I 2 /* IRQ Disable */
#define SM_FLAG_D 3 /* Decimal Mode */
#define SM_FLAG_X 4 /* Index Register Select */
#define SM_FLAG_B 4 /* Break Flag (alias for X flag, in emulation mode) */
#define SM_FLAG_M 5 /* Memory/Acumulator Select */
#define SM_FLAG_V 6 /* Overflow */
#define SM_FLAG_N 7 /* Negative */

#define SM_Cpu_setFlag_NZ8(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_Z, ((data)==0));\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x80));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_NZ16(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_Z, ((data)==0));\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x8000));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_NV8(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_V, ((data)&0x40));\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x80));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_NV16(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_V, ((data)&0x4000));\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x8000));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_N8(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x80));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_N16(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_N, ((data)&0x8000));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_V8(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_V, ((data)&0x40));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_V16(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_V, ((data)&0x4000));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_V(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_V, ((data)));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_Z(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_Z, ((data)==0));\
		m_cpu->reg_psr = psr;\
	}

#define SM_Cpu_setFlag_C(m_cpu, data){\
		Uint8 psr = m_cpu->reg_psr;\
		psr = putBit(psr, SM_FLAG_C, ((data)!=0));\
		m_cpu->reg_psr = psr;\
	}


/**
	MEMORY DATA AND INSTRUCTION ACCESS
*/

#define SM_Cpu_readBus(m_cpu, addr, out_opr){\
		out_opr = SM_Bus_read(m_cpu->io_bus, addr);\
	}

#define SM_Cpu_writeBus(m_cpu, addr, in_opr){\
		SM_Bus_write(m_cpu->io_bus, addr, in_opr);\
	}

Uint8 SM_Cpu_readMem8(SMCpu *m_cpu, Uint16 adr, Uint8 bank);
Uint16 SM_Cpu_readMem16(SMCpu *m_cpu, Uint16 adr, Uint8 bank);

void SM_Cpu_writeMem8(SMCpu *m_cpu, Uint16 adr, Uint8 bank, Uint8 data);
void SM_Cpu_writeMem16(SMCpu *m_cpu, Uint16 adr, Uint8 bank, Uint16 data);

Uint8 SM_Cpu_pop8(SMCpu *m_cpu);
Uint16 SM_Cpu_pop16(SMCpu *m_cpu);

void SM_Cpu_push8(SMCpu *m_cpu, Uint8 data);
void SM_Cpu_push16(SMCpu *m_cpu, Uint16 data);

Uint8 SM_Cpu_fetch8(SMCpu *m_cpu);
Uint16 SM_Cpu_fetch16(SMCpu *m_cpu);


/**
	CPU INTERRUPTIONS
*/

void SM_Cpu_intCall(SMCpu *m_cpu, SMIntType interrupt);
void SM_Cpu_intReturn(SMCpu *m_cpu);


/**
	CPU FUNCTIONS
*/

void SM_Cpu_restart(SMCpu *m_cpu);

void SM_Cpu_step(SMCpu *m_cpu);


#endif // snemus_cpu_h
