#ifndef LIMP32_REGISTER_H_INCLUDED
#define LIMP32_REGISTER_H_INCLUDED

#include "cpu.h"

/**
	REGISTERS ACESSING
*/

#define _l32cpu_grE(l_cpu, reg_name)(l_cpu->regs.reg_name) /// Gets 32-bit register
#define _l32cpu_srE(l_cpu, reg_name, data)(l_cpu->regs.reg_name = data) /// Sets 32-bit register

#define _l32cpu_grX(l_cpu, reg_name)((Uint16)l_cpu->regs.reg_name) /// Gets lower 16-bit register
#define _l32cpu_srX(l_cpu, reg_name, data)(l_cpu->regs.reg_name = (l_cpu->regs.reg_name&0xffff0000)|((Uint16)data)) /// Sets 16-bit register

#define _l32cpu_grL(l_cpu, reg_name)((Uint8)l_cpu->regs.reg_name) /// Gets lower 8-bit register
#define _l32cpu_srL(l_cpu, reg_name, data)(l_cpu->regs.reg_name = (l_cpu->regs.reg_name&0xffffff00)|((Uint8)data)) /// Sets lower 8-bit register

#define _l32cpu_grH(l_cpu, reg_name)((Uint8)(l_cpu->regs.reg_name>>8)) /// Gets higher 8-bit register
#define _l32cpu_srH(l_cpu, reg_name, data)(l_cpu->regs.reg_name = (l_cpu->regs.reg_name&0xffff00ff)|(((Uint8)data)<<8)) /// Sets higher 8-bit register


/**
	GENERAL REGISTERS
*/

/// 32-bit

#define l32cpu_getReg_EAX(l_cpu)(_l32cpu_grE(l_cpu, eax))
#define l32cpu_setReg_EAX(l_cpu, data)(_l32cpu_srE(l_cpu, eax, data))
#define l32cpu_getReg_EDX(l_cpu)(_l32cpu_grE(l_cpu, edx))
#define l32cpu_setReg_EDX(l_cpu, data)(_l32cpu_srE(l_cpu, edx, data))
#define l32cpu_getReg_ECX(l_cpu)(_l32cpu_grE(l_cpu, ecx))
#define l32cpu_setReg_ECX(l_cpu, data)(_l32cpu_srE(l_cpu, ecx, data))
#define l32cpu_getReg_EBX(l_cpu)(_l32cpu_grE(l_cpu, ebx))
#define l32cpu_setReg_EBX(l_cpu, data)(_l32cpu_srE(l_cpu, ebx, data))

#define l32cpu_getReg_ESP(l_cpu)(_l32cpu_grE(l_cpu, esp))
#define l32cpu_setReg_ESP(l_cpu, data)(_l32cpu_srE(l_cpu, esp, data))
#define l32cpu_getReg_EFP(l_cpu)(_l32cpu_grE(l_cpu, efp))
#define l32cpu_setReg_EFP(l_cpu, data)(_l32cpu_srE(l_cpu, efp, data))
#define l32cpu_getReg_ESS(l_cpu)(_l32cpu_grE(l_cpu, ess))
#define l32cpu_setReg_ESS(l_cpu, data)(_l32cpu_srE(l_cpu, ess, data))
#define l32cpu_getReg_ESD(l_cpu)(_l32cpu_grE(l_cpu, esd))
#define l32cpu_setReg_ESD(l_cpu, data)(_l32cpu_srE(l_cpu, esd, data))

/// 16-bit

#define l32cpu_getReg_AX(l_cpu)(_l32cpu_grX(l_cpu, eax))
#define l32cpu_setReg_AX(l_cpu, data)(_l32cpu_srX(l_cpu, eax, data))
#define l32cpu_getReg_DX(l_cpu)(_l32cpu_grX(l_cpu, edx))
#define l32cpu_setReg_DX(l_cpu, data)(_l32cpu_srX(l_cpu, edx, data))
#define l32cpu_getReg_CX(l_cpu)(_l32cpu_grX(l_cpu, ecx))
#define l32cpu_setReg_CX(l_cpu, data)(_l32cpu_srX(l_cpu, ecx, data))
#define l32cpu_getReg_BX(l_cpu)(_l32cpu_grX(l_cpu, ebx))
#define l32cpu_setReg_BX(l_cpu, data)(_l32cpu_srX(l_cpu, ebx, data))

#define l32cpu_getReg_SP(l_cpu)(_l32cpu_grX(l_cpu, esp))
#define l32cpu_setReg_SP(l_cpu, data)(_l32cpu_srX(l_cpu, esp, data))
#define l32cpu_getReg_FL(l_cpu)(_l32cpu_grE(l_cpu, efl_l)) //_l32cpu_grE(l_cpu, efl))
#define l32cpu_setReg_FL(l_cpu, data)(_l32cpu_srE(l_cpu, efl_l, data)) //_l32cpu_srE(l_cpu, efl, data))
#define l32cpu_getReg_SS(l_cpu)(_l32cpu_grE(l_cpu, ess))
#define l32cpu_setReg_SD(l_cpu, data)(_l32cpu_srE(l_cpu, esd, data))

/// 8-bit

#define l32cpu_getReg_AL(l_cpu)(_l32cpu_grL(l_cpu, eax))
#define l32cpu_setReg_AL(l_cpu, data)(_l32cpu_srL(l_cpu, eax, data))
#define l32cpu_getReg_AH(l_cpu)(_l32cpu_grH(l_cpu, eax))
#define l32cpu_setReg_AH(l_cpu, data)(_l32cpu_srH(l_cpu, eax, data))
#define l32cpu_getReg_DL(l_cpu)(_l32cpu_grL(l_cpu, edx))
#define l32cpu_setReg_DL(l_cpu, data)(_l32cpu_srL(l_cpu, edx, data))
#define l32cpu_getReg_DH(l_cpu)(_l32cpu_grH(l_cpu, edx))
#define l32cpu_setReg_DH(l_cpu, data)(_l32cpu_srH(l_cpu, edx, data))
#define l32cpu_getReg_CL(l_cpu)(_l32cpu_grL(l_cpu, ecx))
#define l32cpu_setReg_CL(l_cpu, data)(_l32cpu_srL(l_cpu, ecx, data))
#define l32cpu_getReg_CH(l_cpu)(_l32cpu_grH(l_cpu, ecx))
#define l32cpu_setReg_CH(l_cpu, data)(_l32cpu_srH(l_cpu, ecx, data))
#define l32cpu_getReg_BL(l_cpu)(_l32cpu_grL(l_cpu, ebx))
#define l32cpu_setReg_BL(l_cpu, data)(_l32cpu_srL(l_cpu, ebx, data))
#define l32cpu_getReg_BH(l_cpu)(_l32cpu_grH(l_cpu, ebx))
#define l32cpu_setReg_BH(l_cpu, data)(_l32cpu_srH(l_cpu, ebx, data))


/**
	CONTROL REGISTERS
*/

/// 32-bit

#define l32cpu_getReg_IDTR(l_cpu)(_l32cpu_grE(l_cpu, idtr))
#define l32cpu_setReg_IDTR(l_cpu, data)(_l32cpu_srE(l_cpu, idtr, data))
#define l32cpu_getReg_TR(l_cpu)(_l32cpu_grE(l_cpu, tr))
#define l32cpu_setReg_TR(l_cpu, data)(_l32cpu_srE(l_cpu, tr, data))


/**
	TEST AND DEBUG REGISTERS
*/

#define l32cpu_getReg_DBOC(l_cpu)(_l32cpu_grE(l_cpu, dboc))
#define l32cpu_setReg_DBOC(l_cpu, data)(_l32cpu_srE(l_cpu, dboc, data))
#define l32cpu_getReg_DBOI(l_cpu)(_l32cpu_grE(l_cpu, dboi))
#define l32cpu_setReg_DBOI(l_cpu, data)(_l32cpu_srE(l_cpu, dboi, data))
#define l32cpu_getReg_DBIP(l_cpu)(_l32cpu_grE(l_cpu, dbip))
#define l32cpu_setReg_DBIP(l_cpu, data)(_l32cpu_srE(l_cpu, dbip, data))
#define l32cpu_getReg_DBPR(l_cpu)(_l32cpu_grE(l_cpu, dbpr))
#define l32cpu_setReg_DBPR(l_cpu, data)(_l32cpu_srE(l_cpu, dbpr, data))


#endif // LIMP32_REGISTER_H_INCLUDED
