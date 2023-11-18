#ifndef limp_isa_template_mio_h
#define limp_isa_template_mio_h

#include "../isa.h"


/**
	INSTRUCTION FORMAT: MIO
		Memory Indexed Operands
	
	Affects:
		data_mem => 32
		data_opr => 32
		mem_index => 32
		data_extra => 11
		set_func
*/

#define LI_MIO()\
	LI_MIO_ADM(0, LI_MIO__BASEADR_IMM)\
	LI_MIO_ADM(1, LI_MIO__BASEADR_REGB)\
	LI_MIO_ADM(2, LI_MIO__BASEADR_REGB)\
	LI_MIO_ADM(3, LI_MIO__BASEADR_REGB)

#define LI_MIO_ADM(_li_adm, _li_bafunc)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 0)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 1)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 2)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 3)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 4)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 5)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 6)\
	LI_MIO_ADM_REGB(_li_adm, _li_bafunc, 7)

#define LI_MIO_ADM_REGB(_li_adm, _li_bafunc, _li_regb)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 0)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 1)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 2)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 3)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 4)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 5)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 6)\
	LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, 7)

#define LI_MIO__BASEADR_IMM(_li_regb)\
	LI_CPU_freg_getImm32

#define LI_MIO__BASEADR_REGB(_li_regb)\
	LI_CPU_getReg32_##_li_regb

#define LI_MIO_ADM_REGB_REGO(_li_adm, _li_bafunc, _li_regb, _li_rego)\
	_JP_MIO_##_li_adm##_##_li_regb##_##_li_rego:{\
		Luint32 sc = LI_CPU_freg_getMIO_sc(m_cpu);\
		Luint32 mem_adr = _li_bafunc(_li_regb)(m_cpu);\
		if(_li_adm==2){\
			lif_location = if_location;\
			if_location = &&_JP_MIO_MSRI_##_li_adm##_##_li_regb##_##_li_rego;\
			goto *_JP_GET[8];\
			_JP_MIO_MSRI_##_li_adm##_##_li_regb##_##_li_rego:\
			if_location = lif_location;\
		}\
		else if(_li_adm==3){\
			lif_location = if_location;\
			if_location = &&_JP_MIO_MSRR_##_li_adm##_##_li_regb##_##_li_rego;\
			goto *_JP_GET[LI_CPU_freg_getMIO_regi(m_cpu)];\
			_JP_MIO_MSRR_##_li_adm##_##_li_regb##_##_li_rego:\
			if_location = lif_location;\
		}\
		mem_adr += mem_index<<sc;\
		LIMP_CPU_getMem32(m_cpu, mem_adr, data_mem);\
		data_opr = LI_CPU_getReg32_##_li_rego(m_cpu);\
		data_extra = LI_CPU_freg_getMIO_extra(m_cpu);\
	}\
	goto *if_location;

#define LI_MIOT()\
	static const void* _JP_MIO[256] = {\
		LI_MIOT_ADM(0)\
		LI_MIOT_ADM(1)\
		LI_MIOT_ADM(2)\
		LI_MIOT_ADM(3)\
	};

#define LI_MIOT_ADM(_li_adm)\
	LI_MIOT_ADM_REGB(_li_adm, 0)\
	LI_MIOT_ADM_REGB(_li_adm, 1)\
	LI_MIOT_ADM_REGB(_li_adm, 2)\
	LI_MIOT_ADM_REGB(_li_adm, 3)\
	LI_MIOT_ADM_REGB(_li_adm, 4)\
	LI_MIOT_ADM_REGB(_li_adm, 5)\
	LI_MIOT_ADM_REGB(_li_adm, 6)\
	LI_MIOT_ADM_REGB(_li_adm, 7)\

#define LI_MIOT_ADM_REGB(_li_adm, _li_regb)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 0)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 1)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 2)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 3)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 4)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 5)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 6)\
	LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, 7)

#define LI_MIOT_ADM_REGB_REGO(_li_adm, _li_regb, _li_rego)\
	&&_JP_MIO_##_li_adm##_##_li_regb##_##_li_rego,

#define LI_IS_MIO(_li_name, _li_func)\
	_IS_##_li_name:\
	if_location = &&_ISR_##_li_name;\
	goto *_JP_MIO[LI_CPU_freg_getMIO_descriptor(m_cpu)];\
	_ISR_##_li_name:{\
		_li_func(_li_name##_MIO)\
	}\
	goto _JP_END;


#endif