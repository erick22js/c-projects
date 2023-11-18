#include "register.h"


/**
	REGISTER DATA BY CODE FUNCTIONS
*/

Luint32 LIMP_CPU_getReg_EAX(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_0(m_cpu);
}

Luint32 LIMP_CPU_getReg_EDX(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_1(m_cpu);
}

Luint32 LIMP_CPU_getReg_ECX(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_2(m_cpu);
}

Luint32 LIMP_CPU_getReg_EBX(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_3(m_cpu);
}

Luint32 LIMP_CPU_getReg_EFP(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_4(m_cpu);
}

Luint32 LIMP_CPU_getReg_ESP(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_5(m_cpu);
}

Luint32 LIMP_CPU_getReg_ESS(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_6(m_cpu);
}

Luint32 LIMP_CPU_getReg_ESD(LIMPCpu *m_cpu){
	return LI_CPU_getReg32_7(m_cpu);
}

Luint32 LIMP_CPU_getReg_AX(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_0(m_cpu);
}

Luint32 LIMP_CPU_getReg_DX(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_1(m_cpu);
}

Luint32 LIMP_CPU_getReg_CX(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_2(m_cpu);
}

Luint32 LIMP_CPU_getReg_BX(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_3(m_cpu);
}

Luint32 LIMP_CPU_getReg_FP(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_4(m_cpu);
}

Luint32 LIMP_CPU_getReg_SP(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_5(m_cpu);
}

Luint32 LIMP_CPU_getReg_SS(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_6(m_cpu);
}

Luint32 LIMP_CPU_getReg_SD(LIMPCpu *m_cpu){
	return LI_CPU_getReg16_7(m_cpu);
}

Luint32 LIMP_CPU_getReg_AL(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_0(m_cpu);
}

Luint32 LIMP_CPU_getReg_AH(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_1(m_cpu);
}

Luint32 LIMP_CPU_getReg_DL(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_2(m_cpu);
}

Luint32 LIMP_CPU_getReg_DH(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_3(m_cpu);
}

Luint32 LIMP_CPU_getReg_CL(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_4(m_cpu);
}

Luint32 LIMP_CPU_getReg_CH(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_5(m_cpu);
}

Luint32 LIMP_CPU_getReg_BL(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_6(m_cpu);
}

Luint32 LIMP_CPU_getReg_BH(LIMPCpu *m_cpu){
	return LI_CPU_getReg8_7(m_cpu);
}

void LIMP_CPU_setReg_EAX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_0(m_cpu, data);
}

void LIMP_CPU_setReg_EDX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_1(m_cpu, data);
}

void LIMP_CPU_setReg_ECX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_2(m_cpu, data);
}

void LIMP_CPU_setReg_EBX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_3(m_cpu, data);
}

void LIMP_CPU_setReg_EFP(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_4(m_cpu, data);
}

void LIMP_CPU_setReg_ESP(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_5(m_cpu, data);
}

void LIMP_CPU_setReg_ESS(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_6(m_cpu, data);
}

void LIMP_CPU_setReg_ESD(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg32_7(m_cpu, data);
}

void LIMP_CPU_setReg_AX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_0(m_cpu, data);
}

void LIMP_CPU_setReg_DX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_1(m_cpu, data);
}

void LIMP_CPU_setReg_CX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_2(m_cpu, data);
}

void LIMP_CPU_setReg_BX(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_3(m_cpu, data);
}

void LIMP_CPU_setReg_FP(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_4(m_cpu, data);
}

void LIMP_CPU_setReg_SP(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_5(m_cpu, data);
}

void LIMP_CPU_setReg_SS(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_6(m_cpu, data);
}

void LIMP_CPU_setReg_SD(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg16_7(m_cpu, data);
}

void LIMP_CPU_setReg_AL(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_0(m_cpu, data);
}

void LIMP_CPU_setReg_AH(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_1(m_cpu, data);
}

void LIMP_CPU_setReg_DL(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_2(m_cpu, data);
}

void LIMP_CPU_setReg_DH(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_3(m_cpu, data);
}

void LIMP_CPU_setReg_CL(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_4(m_cpu, data);
}

void LIMP_CPU_setReg_CH(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_5(m_cpu, data);
}

void LIMP_CPU_setReg_BL(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_6(m_cpu, data);
}

void LIMP_CPU_setReg_BH(LIMPCpu *m_cpu, Luint32 data){
	LI_CPU_setReg8_7(m_cpu, data);
}
