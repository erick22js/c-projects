#ifndef limp_isa_util_h
#define limp_isa_util_h

#include "../api.h"


#define LI_DRO_create(opcode, opr, rsd, regd, extra)\
	(((opcode&0xff)<<24)|\
	((opr&0x3)<<22)|\
	((rsd&0x7)<<19)|\
	((regd&0x7)<<16)|\
	((extra&0xffff)))

#define LI_URO_create(opcode, regs, regd, extra)\
	(((opcode&0xff)<<24)|\
	((regs&0x7)<<21)|\
	((regd&0x7)<<18)|\
	((extra&0x3ffff)))

#define LI_IDO_create(opcode, extra)\
	(((opcode&0xff)<<24)|\
	((extra&0xffffff)))

#define LI_IFO_create(opcode, func, extra)\
	(((opcode&0xff)<<24)|\
	((func&0xf)<<20)|\
	((extra&0xfffff)))

#define LI_DFR_create(opcode, tm, regs, regd, extra)\
	(((opcode&0xff)<<24)|\
	((tm&0x3)<<22)|\
	((regs&0x7)<<19)|\
	((regd&0x7)<<16)|\
	((extra&0xffff)))

#define LI_FRO_create(opcode, func, regs, regd, extra)\
	(((opcode&0xff)<<24)|\
	((func&0x1f)<<19)|\
	((regs&0x7)<<16)|\
	((regd&0x7)<<13)|\
	((extra&0x1fff)))

#define LI_FUR_create(opcode, func, rego, extra)\
	(((opcode&0xff)<<24)|\
	((func&0x1f)<<19)|\
	((rego&0x7)<<16)|\
	((extra&0xffff)))

#define LI_MIO_create(opcode, adm, regb, rego, regi, sc, extra)\
	((adm&0x3)>1?(\
	(((opcode&0xff)<<24)|\
	((adm&0x3)<<22)|\
	((regb&0x7)<<19)|\
	((rego&0x7)<<16)|\
	((regi&0x7)<<13)|\
	((sc&0x3)<<11)|\
	((extra&0x7ff)))):(\
	(((opcode&0xff)<<24)|\
	((adm&0x3)<<22)|\
	((regb&0x7)<<19)|\
	((rego&0x7)<<16)|\
	((extra&0xffff)))))


#endif