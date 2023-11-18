#ifndef limp_isa_template_fro_h
#define limp_isa_template_fro_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: FRO
		Functional Registers Operation
	
	Affects:
		data_src => 32
		data_dest => 32
		data_extra => 13
		set_func
*/

#define LI_FRO()\
	LI_FRO_REGS(0)\
	LI_FRO_REGS(1)\
	LI_FRO_REGS(2)\
	LI_FRO_REGS(3)\
	LI_FRO_REGS(4)\
	LI_FRO_REGS(5)\
	LI_FRO_REGS(6)\
	LI_FRO_REGS(7)\

#define LI_FRO_REGS(_li_regs)\
	LI_FRO_REGS_REGD(_li_regs, 0)\
	LI_FRO_REGS_REGD(_li_regs, 1)\
	LI_FRO_REGS_REGD(_li_regs, 2)\
	LI_FRO_REGS_REGD(_li_regs, 3)\
	LI_FRO_REGS_REGD(_li_regs, 4)\
	LI_FRO_REGS_REGD(_li_regs, 5)\
	LI_FRO_REGS_REGD(_li_regs, 6)\
	LI_FRO_REGS_REGD(_li_regs, 7)\

#define LI_FRO_REGS_REGD(_li_regs, _li_regd)\
	_JP_FRO_##_li_regs##_##_li_regd:{\
		data_src = LI_CPU_getReg32_##_li_regs(m_cpu);\
		data_dest = LI_CPU_getReg32_##_li_regd(m_cpu);\
		func = LI_CPU_freg_getFRO_func(m_cpu);\
		data_extra = LI_CPU_freg_getFRO_extra(m_cpu);\
	}\
	goto *if_location;


#define LI_FROT()\
	static const void *_JP_FRO[64] = {\
		LI_FROT_REGS(0)\
		LI_FROT_REGS(1)\
		LI_FROT_REGS(2)\
		LI_FROT_REGS(3)\
		LI_FROT_REGS(4)\
		LI_FROT_REGS(5)\
		LI_FROT_REGS(6)\
		LI_FROT_REGS(7)\
	};

#define LI_FROT_REGS(_li_regs)\
	LI_FROT_REGS_REGD(_li_regs, 0)\
	LI_FROT_REGS_REGD(_li_regs, 1)\
	LI_FROT_REGS_REGD(_li_regs, 2)\
	LI_FROT_REGS_REGD(_li_regs, 3)\
	LI_FROT_REGS_REGD(_li_regs, 4)\
	LI_FROT_REGS_REGD(_li_regs, 5)\
	LI_FROT_REGS_REGD(_li_regs, 6)\
	LI_FROT_REGS_REGD(_li_regs, 7)\

#define LI_FROT_REGS_REGD(_li_regs, _li_regd)\
	&&_JP_FRO_##_li_regs##_##_li_regd,
	

#define LI_IS_FRO(_li_name,\
	_li_func00, _li_func01, _li_func02, _li_func03,\
	_li_func04, _li_func05, _li_func06, _li_func07,\
	_li_func08, _li_func09, _li_func10, _li_func11,\
	_li_func12, _li_func13, _li_func14, _li_func15,\
	_li_func16, _li_func17, _li_func18, _li_func19,\
	_li_func20, _li_func21, _li_func22, _li_func23,\
	_li_func24, _li_func25, _li_func26, _li_func27,\
	_li_func28, _li_func29, _li_func30, _li_func31\
	)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto *_JP_FRO[LI_CPU_freg_getFRO_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		static const void *const _JP_FRO_##_li_name[32] ={\
			&&_JP_FRO_##_li_name##00,\
			&&_JP_FRO_##_li_name##01,\
			&&_JP_FRO_##_li_name##02,\
			&&_JP_FRO_##_li_name##03,\
			&&_JP_FRO_##_li_name##04,\
			&&_JP_FRO_##_li_name##05,\
			&&_JP_FRO_##_li_name##06,\
			&&_JP_FRO_##_li_name##07,\
			&&_JP_FRO_##_li_name##08,\
			&&_JP_FRO_##_li_name##09,\
			&&_JP_FRO_##_li_name##10,\
			&&_JP_FRO_##_li_name##11,\
			&&_JP_FRO_##_li_name##12,\
			&&_JP_FRO_##_li_name##13,\
			&&_JP_FRO_##_li_name##14,\
			&&_JP_FRO_##_li_name##15,\
			&&_JP_FRO_##_li_name##16,\
			&&_JP_FRO_##_li_name##17,\
			&&_JP_FRO_##_li_name##18,\
			&&_JP_FRO_##_li_name##19,\
			&&_JP_FRO_##_li_name##20,\
			&&_JP_FRO_##_li_name##21,\
			&&_JP_FRO_##_li_name##22,\
			&&_JP_FRO_##_li_name##23,\
			&&_JP_FRO_##_li_name##24,\
			&&_JP_FRO_##_li_name##25,\
			&&_JP_FRO_##_li_name##26,\
			&&_JP_FRO_##_li_name##27,\
			&&_JP_FRO_##_li_name##28,\
			&&_JP_FRO_##_li_name##29,\
			&&_JP_FRO_##_li_name##30,\
			&&_JP_FRO_##_li_name##31,\
		};\
		goto *_JP_FRO_##_li_name[func];\
		_JP_FRO_##_li_name##00:{\
			_li_func00(_li_name##_FRO_0)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##01:{\
			_li_func01(_li_name##_FRO_1)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##02:{\
			_li_func02(_li_name##_FRO_2)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##03:{\
			_li_func03(_li_name##_FRO_3)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##04:{\
			_li_func04(_li_name##_FRO_4)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##05:{\
			_li_func05(_li_name##_FRO_5)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##06:{\
			_li_func06(_li_name##_FRO_6)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##07:{\
			_li_func07(_li_name##_FRO_7)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##08:{\
			_li_func08(_li_name##_FRO_8)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##09:{\
			_li_func09(_li_name##_FRO_9)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##10:{\
			_li_func10(_li_name##_FRO_10)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##11:{\
			_li_func11(_li_name##_FRO_11)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##12:{\
			_li_func12(_li_name##_FRO_12)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##13:{\
			_li_func13(_li_name##_FRO_13)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##14:{\
			_li_func14(_li_name##_FRO_14)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##15:{\
			_li_func15(_li_name##_FRO_15)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##16:{\
			_li_func00(_li_name##_FRO_16)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##17:{\
			_li_func01(_li_name##_FRO_17)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##18:{\
			_li_func02(_li_name##_FRO_18)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##19:{\
			_li_func03(_li_name##_FRO_19)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##20:{\
			_li_func04(_li_name##_FRO_20)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##21:{\
			_li_func05(_li_name##_FRO_21)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##22:{\
			_li_func06(_li_name##_FRO_22)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##23:{\
			_li_func07(_li_name##_FRO_23)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##24:{\
			_li_func08(_li_name##_FRO_24)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##25:{\
			_li_func09(_li_name##_FRO_25)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##26:{\
			_li_func10(_li_name##_FRO_26)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##27:{\
			_li_func11(_li_name##_FRO_27)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##28:{\
			_li_func12(_li_name##_FRO_28)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##29:{\
			_li_func13(_li_name##_FRO_29)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##30:{\
			_li_func14(_li_name##_FRO_30)\
		}\
		goto _JP_END;\
		_JP_FRO_##_li_name##31:{\
			_li_func15(_li_name##_FRO_31)\
		}\
		goto _JP_END;\
	}


#endif