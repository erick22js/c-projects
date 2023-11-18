#ifndef limp_isa_template_dro_h
#define limp_isa_template_dro_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: DRO
		Direct Register Operation
	
	Struct:
		opcode:8
		opr:2
		rsd:3
		regd:3
		extra:16
	
	Affects:
		data_src => 8, 16, 32
		data_dest => 8, 16, 32
		data_extra => 16
		set_func
*/

#define LI_DRO()\
	LI_DRO_OPR(8)\
	LI_DRO_OPR(16)\
	LI_DRO_OPR(32)\
	LI_DRO_ADR()

#define LI_DRO_OPR(_li_bitoprs)\
	LI_DRO_OPR_REGS(_li_bitoprs, 0)\
	LI_DRO_OPR_REGS(_li_bitoprs, 1)\
	LI_DRO_OPR_REGS(_li_bitoprs, 2)\
	LI_DRO_OPR_REGS(_li_bitoprs, 3)\
	LI_DRO_OPR_REGS(_li_bitoprs, 4)\
	LI_DRO_OPR_REGS(_li_bitoprs, 5)\
	LI_DRO_OPR_REGS(_li_bitoprs, 6)\
	LI_DRO_OPR_REGS(_li_bitoprs, 7)\

#define LI_DRO_OPR_REGS(_li_bitoprs, _li_regs)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 0)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 1)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 2)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 3)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 4)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 5)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 6)\
	LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, 7)

#define LI_DRO_OPR_REGS_REGD(_li_bitoprs, _li_regs, _li_regd)\
	_JP_DR0##_opr##_li_bitoprs##_##_li_regs##_##_li_regd:{\
		data_src = LI_CPU_getReg##_li_bitoprs##_##_li_regs(m_cpu);\
		data_dest = LI_CPU_getReg##_li_bitoprs##_##_li_regd(m_cpu);\
		set_func = LI_UTIL_BITINDEX2REGCODE(_li_bitoprs, _li_regd);\
		data_extra = LI_CPU_freg_getDRO_extra(m_cpu);\
	}\
	goto *if_location;

#define LI_DRO_ADR()\
	LI_DRO_ADRM(0, 16, 8)\
	LI_DRO_ADRM(1, 16, 16)\
	LI_DRO_ADRM(2, 16, 32)\
	LI_DRO_ADRM(3, 32, 8)\
	LI_DRO_ADRM(4, 32, 16)\
	LI_DRO_ADRM(5, 32, 32)\

#define LI_DRO_ADRM(_li_adrm, _li_bitsrc, _li_bitdest)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 0)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 1)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 2)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 3)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 4)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 5)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 6)\
	LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 7)\
	
#define mcstr(mc) (#mc)

#define LI_DRO_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, _li_regd)\
	_JP_DR0##_adrm##_li_adrm##_##_li_regd:{\
		data_src = LI_CPU_freg_getImm##_li_bitsrc(m_cpu);\
		data_dest = LI_CPU_getReg##_li_bitdest##_##_li_regd(m_cpu);\
		set_func = LI_UTIL_BITINDEX2REGCODE(_li_bitdest, _li_regd);\
		data_extra = 0;\
	}\
	goto *if_location;

#define LI_DROT(_li_name)\
	static const void *const _JP_DR0[256] = {\
		LI_DROT_OPR(8)\
		LI_DROT_OPR(16)\
		LI_DROT_OPR(32)\
		LI_DROT_ADR(_li_name)\
	};

#define LI_DROT_OPR(_li_bitoprs)\
	LI_DROT_OPR_REGS(_li_bitoprs, 0)\
	LI_DROT_OPR_REGS(_li_bitoprs, 1)\
	LI_DROT_OPR_REGS(_li_bitoprs, 2)\
	LI_DROT_OPR_REGS(_li_bitoprs, 3)\
	LI_DROT_OPR_REGS(_li_bitoprs, 4)\
	LI_DROT_OPR_REGS(_li_bitoprs, 5)\
	LI_DROT_OPR_REGS(_li_bitoprs, 6)\
	LI_DROT_OPR_REGS(_li_bitoprs, 7)

#define LI_DROT_OPR_REGS(_li_bitoprs, _li_regs)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 0)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 1)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 2)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 3)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 4)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 5)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 6)\
	LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, 7)

#define LI_DROT_OPR_REGS_REGD(_li_bitoprs, _li_regs, _li_regd)\
	&&_JP_DR0##_opr##_li_bitoprs##_##_li_regs##_##_li_regd,

#define LI_DROT_ADR(_li_name)\
	LI_DROT_ADRM(0, 16, 8)\
	LI_DROT_ADRM(1, 16, 16)\
	LI_DROT_ADRM(2, 16, 32)\
	LI_DROT_ADRM(3, 32, 8)\
	LI_DROT_ADRM(4, 32, 16)\
	LI_DROT_ADRM(5, 32, 32)\
	&&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA,\
	&&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA, &&_JP_INVA,\

#define LI_DROT_ADRM(_li_adrm, _li_bitsrc, _li_bitdest)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 0)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 1)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 2)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 3)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 4)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 5)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 6)\
	LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, 7)

#define LI_DROT_ADRM_REGD(_li_adrm, _li_bitsrc, _li_bitdest, _li_regd)\
	&&_JP_DR0##_adrm##_li_adrm##_##_li_regd,


#define LI_IS_DRO(_li_name, _li_func)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto *_JP_DR0[LI_CPU_freg_getDRO_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		_li_func(_li_name##_DRO)\
	}\
	goto _JP_END;


#endif
