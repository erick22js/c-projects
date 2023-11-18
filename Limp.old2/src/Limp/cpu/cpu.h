#ifndef limp_cpu_h
#define limp_cpu_h

struct LIMPCpu;

#include "../api.h"
#include "../devices/bus.h"
#include "../devices/pci.h"


typedef struct LIMPCpu{
	
	/* Registers */
	
	Luint32 regs_g[8]; /* General Registers */
	
	Luint32 reg_epc; /* Program Counter Register */
	Luint32 reg_fdt; /* Last fetched data Register */
	
	Luint8 reg_lpc; /* Last Program Counter Register */
	
	Luint32 reg_pdtr; /* Pagining Descriptor Table Register */
	Luint32 reg_idtr; /* Interruption Descriptor Table Register */
	Luint32 reg_tdtr; /* Task Descriptor Table Register */
	Luint32 reg_stt; /* Selector Task Table */
	
	/* Program Status Register */
	
	struct LIMPCpuState{
		Lbool cf; /* Carry Flag */
		Lbool bf; /* Borrow Flag */
		Lbool vf; /* Overflow Flag */
		Lbool nf; /* Negative Flag */
		Lbool zf; /* Zero Flag */
		Lbool of; /* Odd Flag */
		Lbool df; /* Direction Flag */
		
		Lbool rn; /* Nested Call (enable Return) */
		Lbool ei; /* Enable External Interruption */
		
		Luint8 pl; /* Privilege Level */
		Lbool pg; /* Pagining */
		Lbool ir; /* Instruction repeating */
	}reg_st;
	
	struct LIMPCpuPins{
		
		/* Devices */
		
		LIMPBus *device_bus;
		LIMPPci *devide_pci;
		
	}pins;
	
}LIMPCpu;


#include "register.h"
#include "mmu.h"
#include "alu.h"
#include "../isa/isa.h"


void LIMP_CPU_init(LIMPCpu *m_cpu);

/* Print the actual CPU state values */

#include <time.h>

void LIMP_CPU_log(LIMPCpu *m_cpu);

void LIMP_CPU_busLog(LIMPCpu *m_cpu, Luint32 offset);

void LIMP_CPU_memLog(LIMPCpu *m_cpu, Luint32 offset);


/**
	CPU Interruption Handdling
*/

typedef enum LICPUIM{
	LICPUIM_abort,
	LICPUIM_trap,
	LICPUIM_fault,
}LICPUIM;

typedef struct LICpuIntType{
	LICPUIM mode;
	Lbool vectored;
	Luint8 selector;
}LICpuIntType;

extern LICpuIntType LICPUINT_00;
extern LICpuIntType LICPUINT_PLRESTRICTION;
extern LICpuIntType LICPUINT_INVOPCODE;
extern LICpuIntType LICPUINT_03;
extern LICpuIntType LICPUINT_DIRNOTAVAIL;
extern LICpuIntType LICPUINT_PAGENOTAVAIL;
extern LICpuIntType LICPUINT_06;
extern LICpuIntType LICPUINT_ZERODIVISION;
extern LICpuIntType LICPUINT_08;
extern LICpuIntType LICPUINT_FPZERODIVISION;
extern LICpuIntType LICPUINT_0A;
extern LICpuIntType LICPUINT_DENIEDDATAACSS;
extern LICpuIntType LICPUINT_DENIEDCODEACSS;
extern LICpuIntType LICPUINT_OVERFLOW;
extern LICpuIntType LICPUINT_0E;
extern LICpuIntType LICPUINT_DEBUGGER;
extern LICpuIntType LICPUINT_SOFTWARE;
extern LICpuIntType LICPUINT_HARDWARE;

void LI_CPU_handdleInt(LIMPCpu *m_cpu, LICpuIntType type, Luint8 selector);

void LIMP_CPU_requestInt(LIMPCpu *m_cpu, LICpuIntType type, Luint8 selector);


/**
	CPU Program Flow
*/

void LIMP_CPU_jumpAbs(LIMPCpu *m_cpu, Luint32 address);

void LIMP_CPU_jumpRel(LIMPCpu *m_cpu, Lsint32 offset);

void LIMP_CPU_step(LIMPCpu *m_cpu);

void LIMP_CPU_execute(LIMPCpu *m_cpu);


#endif
