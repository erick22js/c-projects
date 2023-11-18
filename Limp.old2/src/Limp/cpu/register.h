#ifndef limp_cpu_register_h
#define limp_cpu_register_h

#include "../api.h"

#include "cpu.h"


/**
	GENERAL REGISTER FUNCTIONS
*/

#define LI_CPU_greg(m_cpu, index) m_cpu->regs_g[index]

/* 32-bit Registers */

#define LI_CPU_getRe32(m_cpu, index) LUint32(LI_CPU_greg(m_cpu, index))
#define LI_CPU_setReg32(m_cpu, index, data) (LI_CPU_greg(m_cpu, index) = LUint32(data))

#define LI_CPU_getReg32_0(m_cpu) LI_CPU_getRe32(m_cpu, 0)
#define LI_CPU_setReg32_0(m_cpu, data) LI_CPU_setReg32(m_cpu, 0, data)
#define LI_CPU_getReg32_1(m_cpu) LI_CPU_getRe32(m_cpu, 1)
#define LI_CPU_setReg32_1(m_cpu, data) LI_CPU_setReg32(m_cpu, 1, data)
#define LI_CPU_getReg32_2(m_cpu) LI_CPU_getRe32(m_cpu, 2)
#define LI_CPU_setReg32_2(m_cpu, data) LI_CPU_setReg32(m_cpu, 2, data)
#define LI_CPU_getReg32_3(m_cpu) LI_CPU_getRe32(m_cpu, 3)
#define LI_CPU_setReg32_3(m_cpu, data) LI_CPU_setReg32(m_cpu, 3, data)
#define LI_CPU_getReg32_4(m_cpu) LI_CPU_getRe32(m_cpu, 4)
#define LI_CPU_setReg32_4(m_cpu, data) LI_CPU_setReg32(m_cpu, 4, data)
#define LI_CPU_getReg32_5(m_cpu) LI_CPU_getRe32(m_cpu, 5)
#define LI_CPU_setReg32_5(m_cpu, data) LI_CPU_setReg32(m_cpu, 5, data)
#define LI_CPU_getReg32_6(m_cpu) LI_CPU_getRe32(m_cpu, 6)
#define LI_CPU_setReg32_6(m_cpu, data) LI_CPU_setReg32(m_cpu, 6, data)
#define LI_CPU_getReg32_7(m_cpu) LI_CPU_getRe32(m_cpu, 7)
#define LI_CPU_setReg32_7(m_cpu, data) LI_CPU_setReg32(m_cpu, 7, data)

/* 16-bit Registers */

#define LI_CPU_getReg16(m_cpu, index) LUint16(LI_CPU_greg(m_cpu, index))
#define LI_CPU_setReg16(m_cpu, index, data) (LI_CPU_greg(m_cpu, index) = ((LI_CPU_greg(m_cpu, index)&0xffff0000)|LUint16(data)))

#define LI_CPU_getReg16_0(m_cpu) LI_CPU_getReg16(m_cpu, 0)
#define LI_CPU_setReg16_0(m_cpu, data) (LI_CPU_setReg16(m_cpu, 0, data))
#define LI_CPU_getReg16_1(m_cpu) LI_CPU_getReg16(m_cpu, 1)
#define LI_CPU_setReg16_1(m_cpu, data) (LI_CPU_setReg16(m_cpu, 1, data))
#define LI_CPU_getReg16_2(m_cpu) LI_CPU_getReg16(m_cpu, 2)
#define LI_CPU_setReg16_2(m_cpu, data) (LI_CPU_setReg16(m_cpu, 2, data))
#define LI_CPU_getReg16_3(m_cpu) LI_CPU_getReg16(m_cpu, 3)
#define LI_CPU_setReg16_3(m_cpu, data) (LI_CPU_setReg16(m_cpu, 3, data))
#define LI_CPU_getReg16_4(m_cpu) LI_CPU_getReg16(m_cpu, 4)
#define LI_CPU_setReg16_4(m_cpu, data) (LI_CPU_setReg16(m_cpu, 4, data))
#define LI_CPU_getReg16_5(m_cpu) LI_CPU_getReg16(m_cpu, 5)
#define LI_CPU_setReg16_5(m_cpu, data) (LI_CPU_setReg16(m_cpu, 5, data))
#define LI_CPU_getReg16_6(m_cpu) LI_CPU_getReg16(m_cpu, 6)
#define LI_CPU_setReg16_6(m_cpu, data) (LI_CPU_setReg16(m_cpu, 6, data))
#define LI_CPU_getReg16_7(m_cpu) LI_CPU_getReg16(m_cpu, 7)
#define LI_CPU_setReg16_7(m_cpu, data) (LI_CPU_setReg16(m_cpu, 7, data))

/* 8-bit Registers */

#define LI_CPU_getReg8l(m_cpu, index) LUint8(LI_CPU_greg(m_cpu, index))
#define LI_CPU_getReg8h(m_cpu, index) LUint8(LI_CPU_greg(m_cpu, index)>>8)
#define LI_CPU_setReg8l(m_cpu, index, data) (LI_CPU_greg(m_cpu, index) = ((LI_CPU_greg(m_cpu, index)&0xffffff00)|LUint8(data)))
#define LI_CPU_setReg8h(m_cpu, index, data) (LI_CPU_greg(m_cpu, index) = ((LI_CPU_greg(m_cpu, index)&0xffff00ff)|(LUint8(data)<<8)))

#define LI_CPU_getReg8_0(m_cpu) LI_CPU_getReg8l(m_cpu, 0)
#define LI_CPU_setReg8_0(m_cpu, data) (LI_CPU_setReg8l(m_cpu, 0, data))
#define LI_CPU_getReg8_1(m_cpu) LI_CPU_getReg8h(m_cpu, 0)
#define LI_CPU_setReg8_1(m_cpu, data) (LI_CPU_setReg8h(m_cpu, 0, data))
#define LI_CPU_getReg8_2(m_cpu) LI_CPU_getReg8l(m_cpu, 1)
#define LI_CPU_setReg8_2(m_cpu, data) (LI_CPU_setReg8l(m_cpu, 1, data))
#define LI_CPU_getReg8_3(m_cpu) LI_CPU_getReg8h(m_cpu, 1)
#define LI_CPU_setReg8_3(m_cpu, data) (LI_CPU_setReg8h(m_cpu, 1, data))
#define LI_CPU_getReg8_4(m_cpu) LI_CPU_getReg8l(m_cpu, 2)
#define LI_CPU_setReg8_4(m_cpu, data) (LI_CPU_setReg8l(m_cpu, 2, data))
#define LI_CPU_getReg8_5(m_cpu) LI_CPU_getReg8h(m_cpu, 2)
#define LI_CPU_setReg8_5(m_cpu, data) (LI_CPU_setReg8h(m_cpu, 2, data))
#define LI_CPU_getReg8_6(m_cpu) LI_CPU_getReg8l(m_cpu, 3)
#define LI_CPU_setReg8_6(m_cpu, data) (LI_CPU_setReg8l(m_cpu, 3, data))
#define LI_CPU_getReg8_7(m_cpu) LI_CPU_getReg8h(m_cpu, 3)
#define LI_CPU_setReg8_7(m_cpu, data) (LI_CPU_setReg8h(m_cpu, 3, data))


/**
	FETCH DATA REGISTER FUNCTIONS
*/

#define LI_CPU_freg_fetch(m_cpu) (LIMP_CPU_fetch(m_cpu))

#define LI_CPU_freg(m_cpu) m_cpu->reg_fdt

/* Instruction encoding formats */

/* All Formats */
#define LI_CPU_freg_getOpcode(m_cpu) LUint8(LI_CPU_freg(m_cpu)>>24)

/* DRO Format */
#define LI_CPU_freg_getDRO_opr(m_cpu) ((LI_CPU_freg(m_cpu)>>22)&0x3)
#define LI_CPU_freg_getDRO_rsd(m_cpu) ((LI_CPU_freg(m_cpu)>>19)&0x7)
#define LI_CPU_freg_getDRO_regd(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getDRO_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0xff)
#define LI_CPU_freg_getDRO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0xffff)

/* URO Format */
#define LI_CPU_freg_getURO_regs(m_cpu) ((LI_CPU_freg(m_cpu)>>21)&0x7)
#define LI_CPU_freg_getURO_regd(m_cpu) ((LI_CPU_freg(m_cpu)>>18)&0x7)
#define LI_CPU_freg_getURO_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>18)&0x3f)
#define LI_CPU_freg_getURO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0x3ffff)

/* IDO Format */
#define LI_CPU_freg_getIDO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0xffffff)

/* IFO Format */
#define LI_CPU_freg_getIFO_func(m_cpu) ((LI_CPU_freg(m_cpu)>>20)&0xf)
#define LI_CPU_freg_getIFO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0xfffff)

/* DFR Format */
#define LI_CPU_freg_getDFR_tm(m_cpu) ((LI_CPU_freg(m_cpu)>>22)&0x3)
#define LI_CPU_freg_getDFR_regs(m_cpu) ((LI_CPU_freg(m_cpu)>>19)&0x7)
#define LI_CPU_freg_getDFR_regd(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getDFR_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0xff)
#define LI_CPU_freg_getDFR_extra(m_cpu) (LI_CPU_freg(m_cpu)&0xffff)

/* FRO Format */
#define LI_CPU_freg_getFRO_func(m_cpu) ((LI_CPU_freg(m_cpu)>>19)&0x1f)
#define LI_CPU_freg_getFRO_regd(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getFRO_regs(m_cpu) ((LI_CPU_freg(m_cpu)>>13)&0x7)
#define LI_CPU_freg_getFRO_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>13)&0x3f)
#define LI_CPU_freg_getFRO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0x1fff)

/* FUR Format */
#define LI_CPU_freg_getFUR_func(m_cpu) ((LI_CPU_freg(m_cpu)>>19)&0x1f)
#define LI_CPU_freg_getFUR_rego(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getFUR_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getFUR_extra(m_cpu) (LI_CPU_freg(m_cpu)&0xffff)

/* MIO Format */
#define LI_CPU_freg_getMIO_adm(m_cpu) ((LI_CPU_freg(m_cpu)>>22)&0x3)
#define LI_CPU_freg_getMIO_regb(m_cpu) ((LI_CPU_freg(m_cpu)>>19)&0x7)
#define LI_CPU_freg_getMIO_rego(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0x7)
#define LI_CPU_freg_getMIO_regi(m_cpu) ((LI_CPU_freg(m_cpu)>>13)&0x7)
#define LI_CPU_freg_getMIO_sc(m_cpu) ((LI_CPU_freg(m_cpu)>>11)&0x3)
#define LI_CPU_freg_getMIO_descriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>16)&0xff)
#define LI_CPU_freg_getMIO_idescriptor(m_cpu) ((LI_CPU_freg(m_cpu)>>11)&0x1f)
#define LI_CPU_freg_getMIO_extra(m_cpu) (LI_CPU_freg(m_cpu)&0x7ff)

/* Immediate extracting */
#define LI_CPU_freg_getImm8(m_cpu) LUint8(LI_CPU_freg(m_cpu))
#define LI_CPU_freg_getImm16(m_cpu) LUint16(LI_CPU_freg(m_cpu))
#define LI_CPU_freg_getImm20(m_cpu) (LI_CPU_freg(m_cpu)&0xfffff)
#define LI_CPU_freg_getImm24(m_cpu) (LI_CPU_freg(m_cpu)&0xffffff)
#define LI_CPU_freg_getImm32(m_cpu) (LI_CPU_freg_fetch(m_cpu))


/**
	REGISTER DATA BY CODE FUNCTIONS
*/

Luint32 LIMP_CPU_getReg_EAX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_EDX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_ECX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_EBX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_EFP(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_ESP(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_ESS(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_ESD(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_AX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_DX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_CX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_BX(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_FP(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_SP(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_SS(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_SD(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_AL(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_AH(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_DL(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_DH(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_CL(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_CH(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_BL(LIMPCpu *m_cpu);

Luint32 LIMP_CPU_getReg_BH(LIMPCpu *m_cpu);

void LIMP_CPU_setReg_EAX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_EDX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_ECX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_EBX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_EFP(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_ESP(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_ESS(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_ESD(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_AX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_DX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_CX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_BX(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_FP(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_SP(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_SS(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_SD(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_AL(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_AH(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_DL(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_DH(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_CL(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_CH(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_BL(LIMPCpu *m_cpu, Luint32 data);

void LIMP_CPU_setReg_BH(LIMPCpu *m_cpu, Luint32 data);


/* STATUS Register */
/* L and H prefix means 16-bit data */

#define LIMP_CPU_getReg_STL(m_cpu)(\
	(m_cpu->reg_st.cf)|\
	(m_cpu->reg_st.bf<<1)|\
	(m_cpu->reg_st.vf<<2)|\
	(m_cpu->reg_st.nf<<3)|\
	(m_cpu->reg_st.zf<<4)|\
	(m_cpu->reg_st.of<<5)|\
	(m_cpu->reg_st.df<<6))

#define LIMP_CPU_getReg_STH(m_cpu)(\
	(m_cpu->reg_st.rn)|\
	(m_cpu->reg_st.ei<<1)|\
	((m_cpu->reg_st.pl&3)<<8)|\
	(m_cpu->reg_st.pg<<10)|\
	(m_cpu->reg_st.ir<<11))

#define LIMP_CPU_getReg_ST(m_cpu)(\
	(m_cpu->reg_st.cf)|\
	(m_cpu->reg_st.bf<<1)|\
	(m_cpu->reg_st.vf<<2)|\
	(m_cpu->reg_st.nf<<3)|\
	(m_cpu->reg_st.zf<<4)|\
	(m_cpu->reg_st.of<<5)|\
	(m_cpu->reg_st.df<<6)|\
	(m_cpu->reg_st.rn<<16)|\
	(m_cpu->reg_st.ei<<17)|\
	((m_cpu->reg_st.pl&3)<<24)|\
	(m_cpu->reg_st.pg<<26)|\
	(m_cpu->reg_st.ir<<27))

#define LIMP_CPU_setReg_STL(m_cpu, data){\
		m_cpu->reg_st.cf = data&1;\
		m_cpu->reg_st.bf = (data>>1)&1;\
		m_cpu->reg_st.vf = (data>>2)&1;\
		m_cpu->reg_st.nf = (data>>3)&1;\
		m_cpu->reg_st.zf = (data>>4)&1;\
		m_cpu->reg_st.of = (data>>5)&1;\
		m_cpu->reg_st.df = (data>>6)&1;\
	}

#define LIMP_CPU_setReg_STH(m_cpu, data){\
		m_cpu->reg_st.rn = data&1;\
		m_cpu->reg_st.ei = (data>>1)&1;\
		m_cpu->reg_st.pl = (data>>8)&1;\
		m_cpu->reg_st.pg = (data>>10)&1;\
		m_cpu->reg_st.ir = (data>>11)&1;\
	}

#define LIMP_CPU_setReg_ST(m_cpu, data){\
		m_cpu->reg_st.cf = data&1;\
		m_cpu->reg_st.bf = (data>>1)&1;\
		m_cpu->reg_st.vf = (data>>2)&1;\
		m_cpu->reg_st.nf = (data>>3)&1;\
		m_cpu->reg_st.zf = (data>>4)&1;\
		m_cpu->reg_st.of = (data>>5)&1;\
		m_cpu->reg_st.df = (data>>6)&1;\
		m_cpu->reg_st.rn = (data>>16)&1;\
		m_cpu->reg_st.ei = (data>>17)&1;\
		m_cpu->reg_st.pl = (data>>24)&1;\
		m_cpu->reg_st.pg = (data>>26)&1;\
		m_cpu->reg_st.ir = (data>>27)&1;\
	}


#endif
