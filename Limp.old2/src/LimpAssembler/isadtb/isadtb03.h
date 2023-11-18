#ifndef limpasm_isa_database03_h
#define limpasm_isa_database03_h

#include "template.h"


/**
	ADC
*/
#define LAOPC_ADC_dro 0x06
#define LAOPC_ADC_mio 0x07
	
	LAOPCDTB_TP01("adc", LAOPC_ADC_dro, LAOPC_ADC_mio)
	

/**
	ADD
*/
#define LAOPC_ADD_dro 0x08
#define LAOPC_ADD_mio 0x09
	
	LAOPCDTB_TP01("add", LAOPC_ADD_dro, LAOPC_ADD_mio)
	
	
/**
	SBB
*/
#define LAOPC_SBB_dro 0x0A
#define LAOPC_SBB_mio 0x0B
	
	LAOPCDTB_TP01("sbb", LAOPC_SBB_dro, LAOPC_SBB_mio)
	

/**
	SUB
*/
#define LAOPC_SUB_dro 0x0C
#define LAOPC_SUB_mio 0x0D
	
	LAOPCDTB_TP01("sub", LAOPC_SUB_dro, LAOPC_SUB_mio)
	

/**
	CMP
*/
#define LAOPC_CMP_dro 0x12
#define LAOPC_CMP_mio 0x13
	
	LAOPCDTB_TP01("cmp", LAOPC_CMP_dro, LAOPC_CMP_mio)
	

#endif
