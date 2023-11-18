#include "cpu.h"


void LIMP_CPU_init(LIMPCpu *m_cpu){
	memset(m_cpu, 0, sizeof(LIMPCpu));
	//m_cpu->pins.device_bus = &_LIMPBus_g;
}

/* Print the actual CPU state values */

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
		printf("%8x  ", offset+(row<<4));
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
		printf("%8x  ", offset+(row<<4));
		for(Luint32 col=0; col<16; col++){
			Luint32 adr = offset+(row<<4)+col;
			Luint8 data;
			LIMP_CPU_getMem8(m_cpu, adr, data);
			printf("%.2x ", data);
		}
		printf("\n");
	}
}


/**
	CPU Interruption Handdling
*/

LICpuIntType LICPUINT_00;
LICpuIntType LICPUINT_PLRESTRICTION;
LICpuIntType LICPUINT_INVOPCODE;
LICpuIntType LICPUINT_03;
LICpuIntType LICPUINT_DIRNOTAVAIL;
LICpuIntType LICPUINT_PAGENOTAVAIL;
LICpuIntType LICPUINT_06;
LICpuIntType LICPUINT_ZERODIVISION;
LICpuIntType LICPUINT_08;
LICpuIntType LICPUINT_FPZERODIVISION;
LICpuIntType LICPUINT_0A;
LICpuIntType LICPUINT_DENIEDDATAACSS;
LICpuIntType LICPUINT_DENIEDCODEACSS;
LICpuIntType LICPUINT_OVERFLOW;
LICpuIntType LICPUINT_0E;
LICpuIntType LICPUINT_DEBUGGER;
LICpuIntType LICPUINT_SOFTWARE;
LICpuIntType LICPUINT_HARDWARE;

void LI_CPU_intCall(LIMPCpu *m_cpu, LICpuIntType type, Luint8 selector){
	LIMP_CPU_push(m_cpu, LIMP_CPU_getReg_ST(m_cpu));
	switch(type.mode){
		case LICPUIM_abort:{
			LIMP_CPU_push(m_cpu, m_cpu->reg_epc);
		}
		break;
		case LICPUIM_trap:{
			LIMP_CPU_push(m_cpu, m_cpu->reg_epc);
		}
		break;
		case LICPUIM_fault:{
			LIMP_CPU_push(m_cpu, m_cpu->reg_lpc);
		}
		break;
	}
	
	m_cpu->reg_st.ei = FALSE;
	Luint32 address;
	if(type.vectored){
		address = LIMP_CPU_get_bus32(m_cpu, m_cpu->reg_idtr+(type.selector*4));
	}
	else{
		address = LIMP_CPU_get_bus32(m_cpu, m_cpu->reg_idtr+(selector*4));
	}
	m_cpu->reg_epc = address;
}

void LI_CPU_intReturn(LIMPCpu *m_cpu, LICpuIntType type, Luint8 selector){
	LIMP_CPU_pop(m_cpu, m_cpu->reg_epc);
	Luint32 st = 0;
	LIMP_CPU_pop(m_cpu, st);
	LIMP_CPU_setReg_ST(m_cpu, st);
}

void LIMP_CPU_requestInt(LIMPCpu *m_cpu, LICpuIntType type, Luint8 selector){
	
}


/**
	CPU Program Flow
*/

void LIMP_CPU_jumpAbs(LIMPCpu *m_cpu, Luint32 address){
	m_cpu->reg_epc = address;
}

void LIMP_CPU_jumpRel(LIMPCpu *m_cpu, Lsint32 offset){
	m_cpu->reg_epc = m_cpu->reg_lpc+offset;
}

/* Single instruction stepping */

void LIMP_CPU_step(LIMPCpu *m_cpu){
	m_cpu->reg_lpc = m_cpu->reg_epc;
	LIMP_CPU_fetch(m_cpu);
	LI_ISA(m_cpu);
}

void LIMP_CPU_execute(LIMPCpu *m_cpu){
	m_cpu->reg_lpc = m_cpu->reg_epc;
	LIMP_CPU_fetch(m_cpu);
	LI_ISA(m_cpu);
}

