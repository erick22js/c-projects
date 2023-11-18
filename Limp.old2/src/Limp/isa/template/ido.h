#ifndef limp_isa_template_ido_h
#define limp_isa_template_ido_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: IDO
		Immediate Direct Operation
	
	Affects:
		data_extra => 24
*/

#define LI_IDO()\
	_JP_IDO_:{\
		data_extra = LI_CPU_freg_getIDO_extra(m_cpu);\
	}\
	goto *if_location;

#define LI_IDOT()\
	

#define LI_IS_IDO(_li_name, _li_func)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto _JP_IDO_;\
	_ISR_##_li_name:{\
		_li_func(_li_name##_IDO)\
	}\
	goto _JP_END;


#endif