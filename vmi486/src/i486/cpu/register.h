#ifndef I486_CPU_REGISTER_H_INCLUDED
#define I486_CPU_REGISTER_H_INCLUDED

#include "../types.h"


/*****************************************************************************
* General Registers 32-bit
*/

#define _I486Cpu_getReg_eax(cpu)(cpu->regs.eax)
#define _I486Cpu_setReg_eax(cpu, value)(cpu->regs.eax = value)

#define _I486Cpu_getReg_edx(cpu)(cpu->regs.edx)
#define _I486Cpu_setReg_edx(cpu, value)(cpu->regs.edx = value)

#define _I486Cpu_getReg_ecx(cpu)(cpu->regs.ecx)
#define _I486Cpu_setReg_ecx(cpu, value)(cpu->regs.ecx = value)

#define _I486Cpu_getReg_ebx(cpu)(cpu->regs.ebx)
#define _I486Cpu_setReg_ebx(cpu, value)(cpu->regs.ebx = value)

#define _I486Cpu_getReg_ebp(cpu)(cpu->regs.ebp)
#define _I486Cpu_setReg_ebp(cpu, value)(cpu->regs.ebp = value)

#define _I486Cpu_getReg_esi(cpu)(cpu->regs.esi)
#define _I486Cpu_setReg_esi(cpu, value)(cpu->regs.esi = value)

#define _I486Cpu_getReg_edi(cpu)(cpu->regs.edi)
#define _I486Cpu_setReg_edi(cpu, value)(cpu->regs.edi = value)

#define _I486Cpu_getReg_esp(cpu)(cpu->regs.esp)
#define _I486Cpu_setReg_esp(cpu, value)(cpu->regs.esp = value)


/*****************************************************************************
* General Registers 16-bit
*/

#define _I486Cpu_getReg_ax(cpu)((Uint16)cpu->regs.eax)
#define _I486Cpu_setReg_ax(cpu, value)\
    (cpu->regs.eax = (cpu->regs.eax&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_dx(cpu)((Uint16)cpu->regs.edx)
#define _I486Cpu_setReg_dx(cpu, value)\
    (cpu->regs.edx = (cpu->regs.edx&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_cx(cpu)((Uint16)cpu->regs.ecx)
#define _I486Cpu_setReg_cx(cpu, value)\
    (cpu->regs.ecx = (cpu->regs.ecx&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_bx(cpu)((Uint16)cpu->regs.ebx)
#define _I486Cpu_setReg_bx(cpu, value)\
    (cpu->regs.ebx = (cpu->regs.ebx&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_bp(cpu)((Uint16)cpu->regs.ebp)
#define _I486Cpu_setReg_bp(cpu, value)\
    (cpu->regs.ebp = (cpu->regs.ebp&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_si(cpu)((Uint16)cpu->regs.esi)
#define _I486Cpu_setReg_si(cpu, value)\
    (cpu->regs.esi = (cpu->regs.esi&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_di(cpu)((Uint16)cpu->regs.edi)
#define _I486Cpu_setReg_di(cpu, value)\
    (cpu->regs.edi = (cpu->regs.edi&0xffff0000)|((Uint16)value))

#define _I486Cpu_getReg_sp(cpu)((Uint16)cpu->regs.esp)
#define _I486Cpu_setReg_sp(cpu, value)\
    (cpu->regs.esp = (cpu->regs.esp&0xffff0000)|((Uint16)value))


/*****************************************************************************
* General Registers 16-bit
*/

#define _I486Cpu_getReg_al(cpu)((Uint8)cpu->regs.eax)
#define _I486Cpu_setReg_al(cpu, value)\
    (cpu->regs.eax = (cpu->regs.eax&0xffffff00)|((Uint8)value))
#define _I486Cpu_getReg_ah(cpu)((Uint8)(cpu->regs.eax>>8))
#define _I486Cpu_setReg_ah(cpu, value)\
    (cpu->regs.eax = (cpu->regs.eax&0xffff00ff)|(((Uint8)value)<<8))

#define _I486Cpu_getReg_dl(cpu)((Uint8)cpu->regs.edx)
#define _I486Cpu_setReg_dl(cpu, value)\
    (cpu->regs.edx = (cpu->regs.edx&0xffffff00)|((Uint8)value))
#define _I486Cpu_getReg_dh(cpu)((Uint8)(cpu->regs.edx>>8))
#define _I486Cpu_setReg_dh(cpu, value)\
    (cpu->regs.edx = (cpu->regs.edx&0xffff00ff)|(((Uint8)value)<<8))

#define _I486Cpu_getReg_cl(cpu)((Uint8)cpu->regs.ecx)
#define _I486Cpu_setReg_cl(cpu, value)\
    (cpu->regs.ecx = (cpu->regs.ecx&0xffffff00)|((Uint8)value))
#define _I486Cpu_getReg_ch(cpu)((Uint8)(cpu->regs.ecx>>8))
#define _I486Cpu_setReg_ch(cpu, value)\
    (cpu->regs.ecx = (cpu->regs.ecx&0xffff00ff)|(((Uint8)value)<<8))

#define _I486Cpu_getReg_dl(cpu)((Uint8)cpu->regs.edx)
#define _I486Cpu_setReg_dl(cpu, value)\
    (cpu->regs.edx = (cpu->regs.edx&0xffffff00)|((Uint8)value))
#define _I486Cpu_getReg_dh(cpu)((Uint8)(cpu->regs.edx>>8))
#define _I486Cpu_setReg_dh(cpu, value)\
    (cpu->regs.edx = (cpu->regs.edx&0xffff00ff)|(((Uint8)value)<<8))


/*****************************************************************************
* Segment Registers 32-bit
*/

#define _I486Cpu_getReg_cs(cpu)(cpu->regs.cs)
#define _I486Cpu_setReg_cs(cpu, value)(cpu->regs.cs = value)

#define _I486Cpu_getReg_ss(cpu)(cpu->regs.ss)
#define _I486Cpu_setReg_ss(cpu, value)(cpu->regs.ss = value)

#define _I486Cpu_getReg_ds(cpu)(cpu->regs.ds)
#define _I486Cpu_setReg_ds(cpu, value)(cpu->regs.ds = value)

#define _I486Cpu_getReg_es(cpu)(cpu->regs.es)
#define _I486Cpu_setReg_es(cpu, value)(cpu->regs.es = value)

#define _I486Cpu_getReg_fs(cpu)(cpu->regs.fs)
#define _I486Cpu_setReg_fs(cpu, value)(cpu->regs.fs = value)

#define _I486Cpu_getReg_gs(cpu)(cpu->regs.gs)
#define _I486Cpu_setReg_gs(cpu, value)(cpu->regs.gs = value)


/*****************************************************************************
* Status and Control Registers 32-bit
*/

#define _I486Cpu_getReg_eflags(cpu)(cpu->regs.eflags)
#define _I486Cpu_setReg_eflags(cpu, value)(cpu->regs.eflags = value)

#define _I486Cpu_getReg_eip(cpu)(cpu->regs.eip)
#define _I486Cpu_setReg_eip(cpu, value)(cpu->regs.eip = value)


/*****************************************************************************
* Memory Managment Registers as Segment Descriptor
*/

#define _I486Cpu_reg_gdtr(cpu)(cpu->regs.gdtr)
#define _I486Cpu_reg_ldtr(cpu)(cpu->regs.ldtr)
#define _I486Cpu_reg_idtr(cpu)(cpu->regs.idtr)
#define _I486Cpu_reg_tr(cpu)(cpu->regs.tr)


/*****************************************************************************
* Control Registers 32-bit
*/

#define _I486Cpu_getReg_cr0(cpu)(cpu->regs.cr0)
#define _I486Cpu_setReg_cr0(cpu, value)(cpu->regs.cr0 = value)

#define _I486Cpu_getReg_cr1(cpu)(cpu->regs.cr1)
#define _I486Cpu_setReg_cr1(cpu, value)(cpu->regs.cr1 = value)

#define _I486Cpu_getReg_cr2(cpu)(cpu->regs.cr2)
#define _I486Cpu_setReg_cr2(cpu, value)(cpu->regs.cr2 = value)

#define _I486Cpu_getReg_cr3(cpu)(cpu->regs.cr3)
#define _I486Cpu_setReg_cr3(cpu, value)(cpu->regs.cr3 = value)


/*****************************************************************************
* Test Registers 32-bit
*/

#define _I486Cpu_getReg_dr0(cpu)(cpu->regs.dr0)
#define _I486Cpu_setReg_dr0(cpu, value)(cpu->regs.dr0 = value)

#define _I486Cpu_getReg_dr1(cpu)(cpu->regs.dr1)
#define _I486Cpu_setReg_dr1(cpu, value)(cpu->regs.dr1 = value)

#define _I486Cpu_getReg_dr2(cpu)(cpu->regs.dr2)
#define _I486Cpu_setReg_dr2(cpu, value)(cpu->regs.dr2 = value)

#define _I486Cpu_getReg_dr3(cpu)(cpu->regs.dr3)
#define _I486Cpu_setReg_dr3(cpu, value)(cpu->regs.dr3 = value)

#define _I486Cpu_getReg_dr4(cpu)(cpu->regs.dr4)
#define _I486Cpu_setReg_dr4(cpu, value)(cpu->regs.dr4 = value)

#define _I486Cpu_getReg_dr5(cpu)(cpu->regs.dr5)
#define _I486Cpu_setReg_dr5(cpu, value)(cpu->regs.dr5 = value)

#define _I486Cpu_getReg_dr6(cpu)(cpu->regs.dr6)
#define _I486Cpu_setReg_dr6(cpu, value)(cpu->regs.dr6 = value)

#define _I486Cpu_getReg_dr7(cpu)(cpu->regs.dr7)
#define _I486Cpu_setReg_dr7(cpu, value)(cpu->regs.dr7 = value)

#define _I486Cpu_getReg_tr3(cpu)(cpu->regs.tr3)
#define _I486Cpu_setReg_tr3(cpu, value)(cpu->regs.tr3 = value)

#define _I486Cpu_getReg_tr4(cpu)(cpu->regs.tr4)
#define _I486Cpu_setReg_tr4(cpu, value)(cpu->regs.tr4 = value)

#define _I486Cpu_getReg_tr5(cpu)(cpu->regs.tr5)
#define _I486Cpu_setReg_tr5(cpu, value)(cpu->regs.tr5 = value)

#define _I486Cpu_getReg_tr6(cpu)(cpu->regs.tr6)
#define _I486Cpu_setReg_tr6(cpu, value)(cpu->regs.tr6 = value)

#define _I486Cpu_getReg_tr7(cpu)(cpu->regs.tr7)
#define _I486Cpu_setReg_tr7(cpu, value)(cpu->regs.tr7 = value)


/*****************************************************************************
* EFLAG Register Flags
*/

#define _I486Cpu_getFlag_cf(cpu)((cpu->regs.eflags>>0)&1)
#define _I486Cpu_setFlag_cf(cpu)(cpu->regs.eflags |= (1<<0))
#define _I486Cpu_clrFlag_cf(cpu)(cpu->regs.eflags &= ~(1<<0))

#define _I486Cpu_getFlag_pf(cpu)((cpu->regs.eflags>>2)&1)
#define _I486Cpu_setFlag_pf(cpu)(cpu->regs.eflags |= (1<<2))
#define _I486Cpu_clrFlag_pf(cpu)(cpu->regs.eflags &= ~(1<<2))

#define _I486Cpu_getFlag_af(cpu)((cpu->regs.eflags>>4)&1)
#define _I486Cpu_setFlag_af(cpu)(cpu->regs.eflags |= (1<<4))
#define _I486Cpu_clrFlag_af(cpu)(cpu->regs.eflags &= ~(1<<4))

#define _I486Cpu_getFlag_zf(cpu)((cpu->regs.eflags>>6)&1)
#define _I486Cpu_setFlag_zf(cpu)(cpu->regs.eflags |= (1<<6))
#define _I486Cpu_clrFlag_zf(cpu)(cpu->regs.eflags &= ~(1<<6))

#define _I486Cpu_getFlag_sf(cpu)((cpu->regs.eflags>>7)&1)
#define _I486Cpu_setFlag_sf(cpu)(cpu->regs.eflags |= (1<<7))
#define _I486Cpu_clrFlag_sf(cpu)(cpu->regs.eflags &= ~(1<<7))

#define _I486Cpu_getFlag_tf(cpu)((cpu->regs.eflags>>8)&1)
#define _I486Cpu_setFlag_tf(cpu)(cpu->regs.eflags |= (1<<8))
#define _I486Cpu_clrFlag_tf(cpu)(cpu->regs.eflags &= ~(1<<8))

#define _I486Cpu_getFlag_if(cpu)((cpu->regs.eflags>>9)&1)
#define _I486Cpu_setFlag_if(cpu)(cpu->regs.eflags |= (1<<9))
#define _I486Cpu_clrFlag_if(cpu)(cpu->regs.eflags &= ~(1<<9))

#define _I486Cpu_getFlag_df(cpu)((cpu->regs.eflags>>10)&1)
#define _I486Cpu_setFlag_df(cpu)(cpu->regs.eflags |= (1<<10))
#define _I486Cpu_clrFlag_df(cpu)(cpu->regs.eflags &= ~(1<<10))

#define _I486Cpu_getFlag_of(cpu)((cpu->regs.eflags>>11)&1)
#define _I486Cpu_setFlag_of(cpu)(cpu->regs.eflags |= (1<<11))
#define _I486Cpu_clrFlag_of(cpu)(cpu->regs.eflags &= ~(1<<11))

#define _I486Cpu_getFlag_iopl(cpu)((cpu->regs.eflags>>12)&3)
#define _I486Cpu_setFlag_iopl(cpu, value)(cpu->regs.eflags |= ((value&3)<<12))
#define _I486Cpu_clrFlag_iopl(cpu)(cpu->regs.eflags &= ~(1<<12))

#define _I486Cpu_getFlag_nt(cpu)((cpu->regs.eflags>>14)&1)
#define _I486Cpu_setFlag_nt(cpu)(cpu->regs.eflags |= (1<<14))
#define _I486Cpu_clrFlag_nt(cpu)(cpu->regs.eflags &= ~(1<<14))

#define _I486Cpu_getFlag_rf(cpu)((cpu->regs.eflags>>16)&1)
#define _I486Cpu_setFlag_rf(cpu)(cpu->regs.eflags |= (1<<16))
#define _I486Cpu_clrFlag_rf(cpu)(cpu->regs.eflags &= ~(1<<16))

#define _I486Cpu_getFlag_vm(cpu)((cpu->regs.eflags>>17)&1)
#define _I486Cpu_setFlag_vm(cpu)(cpu->regs.eflags |= (1<<17))
#define _I486Cpu_clrFlag_vm(cpu)(cpu->regs.eflags &= ~(1<<17))

#define _I486Cpu_getFlag_ac(cpu)((cpu->regs.eflags>>18)&1)
#define _I486Cpu_setFlag_ac(cpu)(cpu->regs.eflags |= (1<<18))
#define _I486Cpu_clrFlag_ac(cpu)(cpu->regs.eflags &= ~(1<<18))

#define _I486Cpu_getFlag_vif(cpu)((cpu->regs.eflags>>19)&1)
#define _I486Cpu_setFlag_vif(cpu)(cpu->regs.eflags |= (1<<19))
#define _I486Cpu_clrFlag_vif(cpu)(cpu->regs.eflags &= ~(1<<19))

#define _I486Cpu_getFlag_vip(cpu)((cpu->regs.eflags>>20)&1)
#define _I486Cpu_setFlag_vip(cpu)(cpu->regs.eflags |= (1<<20))
#define _I486Cpu_clrFlag_vip(cpu)(cpu->regs.eflags &= ~(1<<20))

#define _I486Cpu_getFlag_id(cpu)((cpu->regs.eflags>>21)&1)
#define _I486Cpu_setFlag_id(cpu)(cpu->regs.eflags |= (1<<21))
#define _I486Cpu_clrFlag_id(cpu)(cpu->regs.eflags &= ~(1<<21))


/*****************************************************************************
* CR0 Register Flags
*/

#define _I486Cpu_getFlag_pe(cpu)((cpu->regs.cr0>>0)&1)
#define _I486Cpu_setFlag_pe(cpu)(cpu->regs.cr0 |= (1<<0))
#define _I486Cpu_clrFlag_pe(cpu)(cpu->regs.cr0 &= ~(1<<0))

#define _I486Cpu_getFlag_mp(cpu)((cpu->regs.cr0>>1)&1)
#define _I486Cpu_setFlag_mp(cpu)(cpu->regs.cr0 |= (1<<1))
#define _I486Cpu_clrFlag_mp(cpu)(cpu->regs.cr0 &= ~(1<<1))

#define _I486Cpu_getFlag_em(cpu)((cpu->regs.cr0>>2)&1)
#define _I486Cpu_setFlag_em(cpu)(cpu->regs.cr0 |= (1<<2))
#define _I486Cpu_clrFlag_em(cpu)(cpu->regs.cr0 &= ~(1<<2))

#define _I486Cpu_getFlag_ts(cpu)((cpu->regs.cr0>>3)&1)
#define _I486Cpu_setFlag_ts(cpu)(cpu->regs.cr0 |= (1<<3))
#define _I486Cpu_clrFlag_ts(cpu)(cpu->regs.cr0 &= ~(1<<3))

#define _I486Cpu_getFlag_ne(cpu)((cpu->regs.cr0>>5)&1)
#define _I486Cpu_setFlag_ne(cpu)(cpu->regs.cr0 |= (1<<5))
#define _I486Cpu_clrFlag_ne(cpu)(cpu->regs.cr0 &= ~(1<<5))

#define _I486Cpu_getFlag_wp(cpu)((cpu->regs.cr0>>16)&1)
#define _I486Cpu_setFlag_wp(cpu)(cpu->regs.cr0 |= (1<<16))
#define _I486Cpu_clrFlag_wp(cpu)(cpu->regs.cr0 &= ~(1<<16))

#define _I486Cpu_getFlag_am(cpu)((cpu->regs.cr0>>18)&1)
#define _I486Cpu_setFlag_am(cpu)(cpu->regs.cr0 |= (1<<18))
#define _I486Cpu_clrFlag_am(cpu)(cpu->regs.cr0 &= ~(1<<18))

#define _I486Cpu_getFlag_nw(cpu)((cpu->regs.cr0>>19)&1)
#define _I486Cpu_setFlag_nw(cpu)(cpu->regs.cr0 |= (1<<19))
#define _I486Cpu_clrFlag_nw(cpu)(cpu->regs.cr0 &= ~(1<<19))

#define _I486Cpu_getFlag_cd(cpu)((cpu->regs.cr0>>30)&1)
#define _I486Cpu_setFlag_cd(cpu)(cpu->regs.cr0 |= (1<<30))
#define _I486Cpu_clrFlag_cd(cpu)(cpu->regs.cr0 &= ~(1<<30))

#define _I486Cpu_getFlag_pg(cpu)((cpu->regs.cr0>>31)&1)
#define _I486Cpu_setFlag_pg(cpu)(cpu->regs.cr0 |= (1<<31))
#define _I486Cpu_clrFlag_pg(cpu)(cpu->regs.cr0 &= ~(1<<31))


#endif // I486_CPU_REGISTER_H_INCLUDED
