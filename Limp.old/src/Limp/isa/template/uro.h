#ifndef limp_isa_template_uro_h
#define limp_isa_template_uro_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: URO
		Usual Register Operation
	
	Affects:
		data_src => 32
		data_dest => 32
		data_extra => 18
		set_func
*/

#define LI_URO()\
	LI_URO_REGS(0)\
	LI_URO_REGS(1)\
	LI_URO_REGS(2)\
	LI_URO_REGS(3)\
	LI_URO_REGS(4)\
	LI_URO_REGS(5)\
	LI_URO_REGS(6)\
	LI_URO_REGS(7)

#define LI_URO_REGS(_li_regs)\
	LI_URO_REGS_REGD(_li_regs, 0)\
	LI_URO_REGS_REGD(_li_regs, 1)\
	LI_URO_REGS_REGD(_li_regs, 2)\
	LI_URO_REGS_REGD(_li_regs, 3)\
	LI_URO_REGS_REGD(_li_regs, 4)\
	LI_URO_REGS_REGD(_li_regs, 5)\
	LI_URO_REGS_REGD(_li_regs, 6)\
	LI_URO_REGS_REGD(_li_regs, 7)\

#define LI_URO_REGS_REGD(_li_regs, _li_regd)\
	_JP_URO_##_li_regs##_##_li_regd:{\
		data_src = LI_CPU_getReg32_##_li_regs(m_cpu);\
		data_dest = LI_CPU_getReg32_##_li_regd(m_cpu);\
		data_extra = LI_CPU_freg_getURO_extra(m_cpu);\
	}\
	goto *if_location;


#define LI_UROT()\
	static const void* const _JP_URO[64] = {\
		LI_UROT_REGS(0)\
		LI_UROT_REGS(1)\
		LI_UROT_REGS(2)\
		LI_UROT_REGS(3)\
		LI_UROT_REGS(4)\
		LI_UROT_REGS(5)\
		LI_UROT_REGS(6)\
		LI_UROT_REGS(7)\
	};

#define LI_UROT_REGS(_li_regs)\
	LI_UROT_REGS_REGD(_li_regs, 0)\
	LI_UROT_REGS_REGD(_li_regs, 1)\
	LI_UROT_REGS_REGD(_li_regs, 2)\
	LI_UROT_REGS_REGD(_li_regs, 3)\
	LI_UROT_REGS_REGD(_li_regs, 4)\
	LI_UROT_REGS_REGD(_li_regs, 5)\
	LI_UROT_REGS_REGD(_li_regs, 6)\
	LI_UROT_REGS_REGD(_li_regs, 7)\

#define LI_UROT_REGS_REGD(_li_regs, _li_regd)\
	&&_JP_URO_##_li_regs##_##_li_regd,


#define LI_IS_URO(_li_name, _li_func)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto *_JP_URO[LI_CPU_freg_getURO_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		_li_func(_li_name##_URO)\
	}\
	goto _JP_END;


#endif