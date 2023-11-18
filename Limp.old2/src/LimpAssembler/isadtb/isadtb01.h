#ifndef limpasm_isa_database01_h
#define limpasm_isa_database01_h

#include "template.h"


/**
	MOV
*/
#define LAOPC_MOV_dro 0x00
#define LAOPC_MOV_mio 0x01
	
	LAOPCDTB_TP01("mov", LAOPC_MOV_dro, LAOPC_MOV_mio)
	

#endif