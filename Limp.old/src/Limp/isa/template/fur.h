#ifndef limp_isa_template_fur_h
#define limp_isa_template_fur_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: FUR
		Functional Unique Register
	
	Affects:
		data_opr => 32
		data_extra => 16
		set_func
*/

#define LI_FUR()\
	LI_FUR_REGO(0)\
	LI_FUR_REGO(1)\
	LI_FUR_REGO(2)\
	LI_FUR_REGO(3)\
	LI_FUR_REGO(4)\
	LI_FUR_REGO(5)\
	LI_FUR_REGO(6)\
	LI_FUR_REGO(7)\

#define LI_FUR_REGO(_li_rego)\
	_JP_FUR_##_li_rego:{\
		data_opr = LI_CPU_getReg32_##_li_rego(m_cpu);\
		func = LI_CPU_freg_getFRO_func(m_cpu);\
		data_extra = LI_CPU_freg_getFUR_extra(m_cpu);\
	}\
	goto *if_location;


#define LI_FURT()\
	static const void *_JP_FUR[8] = {\
		LI_FURT_REGO(0)\
		LI_FURT_REGO(1)\
		LI_FURT_REGO(2)\
		LI_FURT_REGO(3)\
		LI_FURT_REGO(4)\
		LI_FURT_REGO(5)\
		LI_FURT_REGO(6)\
		LI_FURT_REGO(7)\
	};

#define LI_FURT_REGO(_li_rego)\
	&&_JP_FUR_##_li_rego,
	

#define LI_IS_FUR(_li_name,\
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
	goto *_JP_FUR[LI_CPU_freg_getFUR_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		static const void *const _JP_FUR_##_li_name[32] ={\
			&&_JP_FUR_##_li_name##00,\
			&&_JP_FUR_##_li_name##01,\
			&&_JP_FUR_##_li_name##02,\
			&&_JP_FUR_##_li_name##03,\
			&&_JP_FUR_##_li_name##04,\
			&&_JP_FUR_##_li_name##05,\
			&&_JP_FUR_##_li_name##06,\
			&&_JP_FUR_##_li_name##07,\
			&&_JP_FUR_##_li_name##08,\
			&&_JP_FUR_##_li_name##09,\
			&&_JP_FUR_##_li_name##10,\
			&&_JP_FUR_##_li_name##11,\
			&&_JP_FUR_##_li_name##12,\
			&&_JP_FUR_##_li_name##13,\
			&&_JP_FUR_##_li_name##14,\
			&&_JP_FUR_##_li_name##15,\
			&&_JP_FUR_##_li_name##16,\
			&&_JP_FUR_##_li_name##17,\
			&&_JP_FUR_##_li_name##18,\
			&&_JP_FUR_##_li_name##19,\
			&&_JP_FUR_##_li_name##20,\
			&&_JP_FUR_##_li_name##21,\
			&&_JP_FUR_##_li_name##22,\
			&&_JP_FUR_##_li_name##23,\
			&&_JP_FUR_##_li_name##24,\
			&&_JP_FUR_##_li_name##25,\
			&&_JP_FUR_##_li_name##26,\
			&&_JP_FUR_##_li_name##27,\
			&&_JP_FUR_##_li_name##28,\
			&&_JP_FUR_##_li_name##29,\
			&&_JP_FUR_##_li_name##30,\
			&&_JP_FUR_##_li_name##31,\
		};\
		goto *_JP_FUR_##_li_name[func];\
		_JP_FUR_##_li_name##00:{\
			_li_func00(_li_name##_FUR_0)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##01:{\
			_li_func01(_li_name##_FUR_1)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##02:{\
			_li_func02(_li_name##_FUR_2)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##03:{\
			_li_func03(_li_name##_FUR_3)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##04:{\
			_li_func04(_li_name##_FUR_4)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##05:{\
			_li_func05(_li_name##_FUR_5)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##06:{\
			_li_func06(_li_name##_FUR_6)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##07:{\
			_li_func07(_li_name##_FUR_7)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##08:{\
			_li_func08(_li_name##_FUR_8)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##09:{\
			_li_func09(_li_name##_FUR_9)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##10:{\
			_li_func10(_li_name##_FUR_10)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##11:{\
			_li_func11(_li_name##_FUR_11)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##12:{\
			_li_func12(_li_name##_FUR_12)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##13:{\
			_li_func13(_li_name##_FUR_13)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##14:{\
			_li_func14(_li_name##_FUR_14)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##15:{\
			_li_func15(_li_name##_FUR_15)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##16:{\
			_li_func00(_li_name##_FUR_16)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##17:{\
			_li_func01(_li_name##_FUR_17)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##18:{\
			_li_func02(_li_name##_FUR_18)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##19:{\
			_li_func03(_li_name##_FUR_19)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##20:{\
			_li_func04(_li_name##_FUR_20)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##21:{\
			_li_func05(_li_name##_FUR_21)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##22:{\
			_li_func06(_li_name##_FUR_22)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##23:{\
			_li_func07(_li_name##_FUR_23)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##24:{\
			_li_func08(_li_name##_FUR_24)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##25:{\
			_li_func09(_li_name##_FUR_25)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##26:{\
			_li_func10(_li_name##_FUR_26)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##27:{\
			_li_func11(_li_name##_FUR_27)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##28:{\
			_li_func12(_li_name##_FUR_28)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##29:{\
			_li_func13(_li_name##_FUR_29)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##30:{\
			_li_func14(_li_name##_FUR_30)\
		}\
		goto _JP_END;\
		_JP_FUR_##_li_name##31:{\
			_li_func15(_li_name##_FUR_31)\
		}\
		goto _JP_END;\
	}


#endif