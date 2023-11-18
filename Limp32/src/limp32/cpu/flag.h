#ifndef LIMP32_FLAG_H_INCLUDED
#define LIMP32_FLAG_H_INCLUDED

#include "cpu.h"


/**
	REGISTER FLAGS ACCESS
*/

#define _l32cpu_eflags_l(l_cpu)(l_cpu->regs.efl_l)
#define _l32cpu_eflags_h(l_cpu)(l_cpu->regs.efl_h)


/**
	APPLICATION FLAGS
*/

#define l32cpu_getFlag_CF(l_cpu)((_l32cpu_eflags_l(l_cpu)>>0)&1)
#define l32cpu_setFlag_CF(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<0))
#define l32cpu_clrFlag_CF(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<0)))
#define l32cpu_togFlag_CF(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<0))

#define l32cpu_getFlag_VF(l_cpu)((_l32cpu_eflags_l(l_cpu)>>1)&1)
#define l32cpu_setFlag_VF(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<1))
#define l32cpu_clrFlag_VF(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<1)))
#define l32cpu_togFlag_VF(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<1))

#define l32cpu_getFlag_NF(l_cpu)((_l32cpu_eflags_l(l_cpu)>>2)&1)
#define l32cpu_setFlag_NF(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<2))
#define l32cpu_clrFlag_NF(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<2)))
#define l32cpu_togFlag_NF(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<2))

#define l32cpu_getFlag_ZF(l_cpu)((_l32cpu_eflags_l(l_cpu)>>3)&1)
#define l32cpu_setFlag_ZF(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<3))
#define l32cpu_clrFlag_ZF(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<3)))
#define l32cpu_togFlag_ZF(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<3))

#define l32cpu_getFlag_OF(l_cpu)((_l32cpu_eflags_l(l_cpu)>>4)&1)
#define l32cpu_setFlag_OF(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<4))
#define l32cpu_clrFlag_OF(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<4)))
#define l32cpu_togFlag_OF(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<4))

#define l32cpu_getFlag_RN(l_cpu)((_l32cpu_eflags_l(l_cpu)>>5)&1)
#define l32cpu_setFlag_RN(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<5))
#define l32cpu_clrFlag_RN(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<5)))
#define l32cpu_togFlag_RN(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<5))

#define l32cpu_getFlag_DR(l_cpu)((_l32cpu_eflags_l(l_cpu)>>6)&1)
#define l32cpu_setFlag_DR(l_cpu)(_l32cpu_eflags_l(l_cpu)|=(1<<6))
#define l32cpu_clrFlag_DR(l_cpu)(_l32cpu_eflags_l(l_cpu)&=(~(1<<6)))
#define l32cpu_togFlag_DR(l_cpu)(_l32cpu_eflags_l(l_cpu)^=(1<<6))


/**
	SYSTEM FLAGS
*/

#define l32cpu_getFlag_PL(l_cpu)((_l32cpu_eflags_h(l_cpu)>>0)&3)
#define l32cpu_setFlag_PL(l_cpu, data)(_l32cpu_eflags_h(l_cpu)=(_l32cpu_eflags_h(l_cpu)&(3<<0))|((data&3)<<0))

#define l32cpu_getFlag_IF(l_cpu)((_l32cpu_eflags_h(l_cpu)>>2)&1)
#define l32cpu_setFlag_IF(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<2))
#define l32cpu_clrFlag_IF(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<2)))
#define l32cpu_togFlag_IF(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<2))

#define l32cpu_getFlag_PG(l_cpu)((_l32cpu_eflags_h(l_cpu)>>3)&1)
#define l32cpu_setFlag_PG(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<3))
#define l32cpu_clrFlag_PG(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<3)))
#define l32cpu_togFlag_PG(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<3))

#define l32cpu_getFlag_PD(l_cpu)((_l32cpu_eflags_h(l_cpu)>>4)&1)
#define l32cpu_setFlag_PD(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<4))
#define l32cpu_clrFlag_PD(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<4)))
#define l32cpu_togFlag_DP(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<4))

#define l32cpu_getFlag_DB(l_cpu)((_l32cpu_eflags_h(l_cpu)>>5)&1)
#define l32cpu_setFlag_DB(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<5))
#define l32cpu_clrFlag_DB(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<5)))
#define l32cpu_togFlag_DB(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<5))

#define l32cpu_getFlag_NT(l_cpu)((_l32cpu_eflags_h(l_cpu)>>6)&1)
#define l32cpu_setFlag_NT(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<6))
#define l32cpu_clrFlag_NT(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<6)))
#define l32cpu_togFlag_NT(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<6))

#define l32cpu_getFlag_IR(l_cpu)((_l32cpu_eflags_h(l_cpu)>>7)&1)
#define l32cpu_setFlag_IR(l_cpu)(_l32cpu_eflags_h(l_cpu)|=(1<<7))
#define l32cpu_clrFlag_IR(l_cpu)(_l32cpu_eflags_h(l_cpu)&=(~(1<<7)))
#define l32cpu_togFlag_IR(l_cpu)(_l32cpu_eflags_h(l_cpu)^=(1<<7))


#endif // LIMP32_FLAG_H_INCLUDED
