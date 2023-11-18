#ifndef limp_isaset_arithmetic_h
#define limp_isaset_arithmetic_h

#include "../template/dro.h"
#include "../template/mio.h"


/**
		ADC
	
	Adds a value operand with carry to destination.
	
*/

#define _LISDF_ADC_dro(_id)\
	LI_ALU_ADC(m_cpu, data_dest, data_src, data_set);\
	LI_IS_SET(_id)

#define _LISD_06()\
	LI_IS_DRO(ID06, _LISDF_ADC_dro);\

#define _LISDF_ADC_mio(_id)\
	LI_ALU_ADC(m_cpu, data_opr, data_mem, data_set);\
	LI_IS_SET(_id)

#define _LISD_07()\
	LI_IS_MIO(ID07, _LISDF_ADC_mio);\


/**
		ADD
	
	Adds a value operand to destination.
	
*/

#define _LISDF_ADD_dro(_id)\
	LI_ALU_ADD(m_cpu, data_dest, data_src, data_set);\
	LI_IS_SET(_id)

#define _LISD_08()\
	LI_IS_DRO(ID08, _LISDF_ADD_dro);\

#define _LISDF_ADD_mio(_id)\
	LI_ALU_ADD(m_cpu, data_opr, data_mem, data_set);\
	LI_IS_SET(_id)

#define _LISD_09()\
	LI_IS_MIO(ID09, _LISDF_ADD_mio);\


/**
		SBB
	
	Subtracts a value operand with borrow from destination.
	
*/

#define _LISDF_SBB_dro(_id)\
	LI_ALU_SBB(m_cpu, data_dest, data_src, data_set);\
	LI_IS_SET(_id)

#define _LISD_0A()\
	LI_IS_DRO(ID0A, _LISDF_SBB_dro);\

#define _LISDF_SBB_mio(_id)\
	LI_ALU_SBB(m_cpu, data_opr, data_mem, data_set);\
	LI_IS_SET(_id)

#define _LISD_0B()\
	LI_IS_MIO(ID0B, _LISDF_SBB_mio);\


/**
		SUB
	
	Subtracts a value operand from destination.
	
*/

#define _LISDF_SUB_dro(_id)\
	LI_ALU_SUB(m_cpu, data_dest, data_src, data_set);\
	LI_IS_SET(_id)

#define _LISD_0C()\
	LI_IS_DRO(ID0C, _LISDF_SUB_dro);\

#define _LISDF_SUB_mio(_id)\
	LI_ALU_SUB(m_cpu, data_opr, data_mem, data_set);\
	LI_IS_SET(_id)

#define _LISD_0D()\
	LI_IS_MIO(ID0D, _LISDF_SUB_mio);\


/**
		CMP
	
	Comparates a value operand to destination.
	
*/

#define _LISDF_CMP_dro(_id)\
	LI_ALU_SUB(m_cpu, data_dest, data_src, data_set);

#define _LISD_12()\
	LI_IS_DRO(ID12, _LISDF_CMP_dro);\

#define _LISDF_CMP_mio(_id)\
	LI_ALU_SUB(m_cpu, data_opr, data_mem, data_set);

#define _LISD_13()\
	LI_IS_MIO(ID13, _LISDF_CMP_mio);\



#endif
