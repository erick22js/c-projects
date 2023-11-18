#ifndef limp_isa_template_ifo_h
#define limp_isa_template_ifo_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: IFO
		Immediate Functional Operation
	
	Affects:
		data_extra => 20
		set_func
*/

#define LI_IFO()\
	_JP_IFO_:{\
		func = LI_CPU_freg_getIFO_func(m_cpu);\
		data_extra = LI_CPU_freg_getIFO_extra(m_cpu);\
	}\
	goto *if_location;

#define LI_IFOT()\
	

#define LI_IS_IFO(_li_name,\
	_li_func00, _li_func01, _li_func02, _li_func03,\
	_li_func04, _li_func05, _li_func06, _li_func07,\
	_li_func08, _li_func09, _li_func10, _li_func11,\
	_li_func12, _li_func13, _li_func14, _li_func15\
	)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto _JP_IFO_;\
	_ISR_##_li_name:{\
		static const void *const _JP_IFO_##_li_name[16] ={\
			&&_JP_IFO_##_li_name##00,\
			&&_JP_IFO_##_li_name##01,\
			&&_JP_IFO_##_li_name##02,\
			&&_JP_IFO_##_li_name##03,\
			&&_JP_IFO_##_li_name##04,\
			&&_JP_IFO_##_li_name##05,\
			&&_JP_IFO_##_li_name##06,\
			&&_JP_IFO_##_li_name##07,\
			&&_JP_IFO_##_li_name##08,\
			&&_JP_IFO_##_li_name##09,\
			&&_JP_IFO_##_li_name##10,\
			&&_JP_IFO_##_li_name##11,\
			&&_JP_IFO_##_li_name##12,\
			&&_JP_IFO_##_li_name##13,\
			&&_JP_IFO_##_li_name##14,\
			&&_JP_IFO_##_li_name##15,\
		};\
		goto *_JP_IFO_##_li_name[func];\
		_JP_IFO_##_li_name##00:{\
			_li_func00(_li_name##_IFO_0)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##01:{\
			_li_func01(_li_name##_IFO_1)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##02:{\
			_li_func02(_li_name##_IFO_2)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##03:{\
			_li_func03(_li_name##_IFO_3)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##04:{\
			_li_func04(_li_name##_IFO_4)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##05:{\
			_li_func05(_li_name##_IFO_5)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##06:{\
			_li_func06(_li_name##_IFO_6)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##07:{\
			_li_func07(_li_name##_IFO_7)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##08:{\
			_li_func08(_li_name##_IFO_8)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##09:{\
			_li_func09(_li_name##_IFO_9)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##10:{\
			_li_func10(_li_name##_IFO_10)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##11:{\
			_li_func11(_li_name##_IFO_11)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##12:{\
			_li_func12(_li_name##_IFO_12)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##13:{\
			_li_func13(_li_name##_IFO_13)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##14:{\
			_li_func14(_li_name##_IFO_14)\
		}\
		goto _JP_END;\
		_JP_IFO_##_li_name##15:{\
			_li_func15(_li_name##_IFO_15)\
		}\
		goto _JP_END;\
	}


#endif