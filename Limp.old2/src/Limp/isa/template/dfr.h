#ifndef limp_isa_template_dfr_h
#define limp_isa_template_dfr_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: DFR
		Differents Registers Types Operation
	
	Affects:
		data_src => 8, 16
		data_dest => 16, 32
		data_extra => 16
		set_func
*/

#define LI_DFR()\
	LI_DFR_TM(0, 8, 32)\
	LI_DFR_TM(1, 16, 32)\
	LI_DFR_TM(2, 8, 16)\
	LI_DFR_TMI()

#define LI_DFR_TM(_li_tm, _li_bs, _li_bd)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 0)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 1)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 2)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 3)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 4)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 5)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 6)\
	LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, 7)

#define LI_DFR_TM_REGS(_li_tm, _li_bs, _li_bd, _li_regs)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 0)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 1)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 2)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 3)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 4)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 5)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 6)\
	LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 7)

#define LI_DFR_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, _li_regd)\
	_JP_DFR_##_li_tm##_##_li_regs##_##_li_regd:{\
		data_src = L##_li_bs##T32(LI_CPU_getReg##_li_bs##_##_li_regs(m_cpu));\
		data_dest = L##_li_bd##T32(LI_CPU_getReg##_li_bd##_##_li_regd(m_cpu));\
		set_func = LI_UTIL_BITINDEX2REGCODE(_li_bd, _li_regd);\
		data_extra = LI_CPU_freg_getDFR_extra(m_cpu);\
	}\
	goto *if_location;

#define LI_DFR_TMI()\
	LI_DFR_TMI_REGD(0)\
	LI_DFR_TMI_REGD(1)\
	LI_DFR_TMI_REGD(2)\
	LI_DFR_TMI_REGD(3)\
	LI_DFR_TMI_REGD(4)\
	LI_DFR_TMI_REGD(5)\
	LI_DFR_TMI_REGD(6)\
	LI_DFR_TMI_REGD(7)

#define LI_DFR_TMI_REGD(_li_regd)\
	_JP_DFR_IMM_##_li_regd:{\
		data_src = L16T32(LI_CPU_freg_getDFR_extra(m_cpu));\
		data_dest = LI_CPU_getReg32_##_li_regd(m_cpu);\
		set_func = LI_UTIL_BITINDEX2REGCODE(32, _li_regd);\
		data_extra = data_src;\
	}\
	goto *if_location;

#define LI_DFRT()\
	static const void *_JP_DFR[256] = {\
		LI_DFRT_TM(0, 8, 32)\
		LI_DFRT_TM(1, 16, 32)\
		LI_DFRT_TM(2, 8, 16)\
		LI_DFRT_TMI()\
	};

#define LI_DFRT_TM(_li_tm, _li_bs, _li_bd)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 0)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 1)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 2)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 3)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 4)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 5)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 6)\
	LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, 7)

#define LI_DFRT_TM_REGS(_li_tm, _li_bs, _li_bd, _li_regs)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 0)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 1)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 2)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 3)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 4)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 5)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 6)\
	LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, 7)

#define LI_DFRT_TM_REGS_REGD(_li_tm, _li_bs, _li_bd, _li_regs, _li_regd)\
	&&_JP_DFR_##_li_tm##_##_li_regs##_##_li_regd,
	
#define LI_DFRT_TMI()\
	LI_DFRT_TMI_REGD(0)\
	LI_DFRT_TMI_REGD(1)\
	LI_DFRT_TMI_REGD(2)\
	LI_DFRT_TMI_REGD(3)\
	LI_DFRT_TMI_REGD(4)\
	LI_DFRT_TMI_REGD(5)\
	LI_DFRT_TMI_REGD(6)\
	LI_DFRT_TMI_REGD(7)

#define LI_DFRT_TMI_REGD(_li_regd)\
	&&_JP_DFR_IMM_##_li_regd,
	

#define LI_IS_DFR(_li_name, _li_func)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto *_JP_DFR[LI_CPU_freg_getDFR_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		_li_func(_li_name##_DFR)\
	}\
	goto _JP_END;
	


#endif
