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


void LIMP_CPU_init(LIMPCpu *m_cpu){
	memset(m_cpu, 0, sizeof(LIMPCpu));
	
	m_cpu->pins.device_bus = &_LIMPBus_g;
}

/* Print the actual CPU state values */

#include <time.h>

void LIMP_CPU_log(LIMPCpu *m_cpu){
	
	time_t tempo;
	time(&tempo);
	printf("=====================================================\n\tLIMP CPU AT: %s\n", ctime(&tempo));
	
	
	/* Print the registers */
	
	printf("@ Registers (Software)\n");
	
	printf("* EAX:  %8x;  ", LIMP_CPU_getReg_EAX(m_cpu));
	printf("AX: %4x;  ", LIMP_CPU_getReg_AX(m_cpu));
	printf("AH/AL: %2x %2x\n", LIMP_CPU_getReg_AH(m_cpu), LIMP_CPU_getReg_AL(m_cpu));
	
	printf("* EDX:  %8x;  ", LIMP_CPU_getReg_EDX(m_cpu));
	printf("DX: %4x;  ", LIMP_CPU_getReg_DX(m_cpu));
	printf("DH/DL: %2x %2x\n", LIMP_CPU_getReg_DH(m_cpu), LIMP_CPU_getReg_DL(m_cpu));
	
	printf("* ECX:  %8x;  ", LIMP_CPU_getReg_ECX(m_cpu));
	printf("CX: %4x;  ", LIMP_CPU_getReg_CX(m_cpu));
	printf("CH/CL: %2x %2x\n", LIMP_CPU_getReg_CH(m_cpu), LIMP_CPU_getReg_CL(m_cpu));
	
	printf("* EBX:  %8x;  ", LIMP_CPU_getReg_EBX(m_cpu));
	printf("BX: %4x;  ", LIMP_CPU_getReg_BX(m_cpu));
	printf("BH/BL: %2x %2x\n", LIMP_CPU_getReg_BH(m_cpu), LIMP_CPU_getReg_BL(m_cpu));
	
	printf("* EFP:  %8x;  ", LIMP_CPU_getReg_EFP(m_cpu));
	printf("FP: %4x\n", LIMP_CPU_getReg_FP(m_cpu));
	
	printf("* ESP:  %8x;  ", LIMP_CPU_getReg_ESP(m_cpu));
	printf("SP: %4x\n", LIMP_CPU_getReg_SP(m_cpu));
	
	printf("* ESS:  %8x;  ", LIMP_CPU_getReg_ESS(m_cpu));
	printf("SS: %4x\n", LIMP_CPU_getReg_SS(m_cpu));
	
	printf("* ESD:  %8x;  ", LIMP_CPU_getReg_ESD(m_cpu));
	printf("SD: %4x\n", LIMP_CPU_getReg_SD(m_cpu));
	
	printf("\n@ Registers (Hardware)\n");
	
	printf("* EPC:  %8x\n", m_cpu->reg_epc);
	printf("* FDT:  %8x\n", m_cpu->reg_fdt);
	
	printf("\n@ Registers (Control)\n");
	
	printf("* PDTR: %8x\n", m_cpu->reg_pdtr);
	printf("* IDTR: %8x\n", m_cpu->reg_idtr);
	printf("* TDTR: %8x\n", m_cpu->reg_tdtr);
	printf("* STT:  %8x\n", m_cpu->reg_stt);
	
	
	/* Print Program State */
	
	printf("\n@ Program State\n");
	
	printf(" CF BF VF NF ZF OF DF   RN EI   PL PG IR\n\
 %x  %x  %x  %x  %x  %x  %x    %x  %x    %x  %x  %x\n",
		m_cpu->reg_st.cf, m_cpu->reg_st.bf, 
		m_cpu->reg_st.vf, m_cpu->reg_st.nf, 
		m_cpu->reg_st.zf, m_cpu->reg_st.of, 
		m_cpu->reg_st.df, 
		m_cpu->reg_st.rn, m_cpu->reg_st.ei, 
		m_cpu->reg_st.pl, 
		m_cpu->reg_st.pg, m_cpu->reg_st.ir);
}

void LIMP_CPU_busLog(LIMPCpu *m_cpu, Luint32 offset){
	printf("=====================================================\n\tLIMP BUS at 0x%x\n\n", offset);
	
	printf("           0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n\n");
	for(Luint32 row=0; row<16; row++){
		printf("%.8x  ", offset+(row<<4));
		for(Luint32 col=0; col<16; col++){
			Luint32 adr = offset+(row<<4)+col;
			Luint8 data;
			data = LIMP_CPU_get_bus8(m_cpu, adr);
			printf("%.2x ", data);
		}
		printf("\n");
	}
}

void LIMP_CPU_memLog(LIMPCpu *m_cpu, Luint32 offset){
	printf("=====================================================\n\tLIMP MEM at 0x%x\n\n", offset);
	
	printf("           0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n\n");
	for(Luint32 row=0; row<16; row++){
		printf("%.8x  ", offset+(row<<4));
		for(Luint32 col=0; col<16; col++){
			Luint32 adr = offset+(row<<4)+col;
			Luint8 data;
			LIMP_CPU_getMem8(m_cpu, adr, data);
			printf("%.2x ", data);
		}
		printf("\n");
	}
}


#endif