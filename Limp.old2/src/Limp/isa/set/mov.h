#ifndef limp_isaset_mov_h
#define limp_isaset_mov_h

#include "../template/dro.h"
#include "../template/mio.h"

/**
		MOV
	
	Moves a value operand from operand to destination (Unsigned).
	
	# DRO: 00
		mov reg, reg
		mov reg, imm16
		mov reg, imm32
	
	# MIO: 01
		mov r32, [imm32]
		mov r32, [r32]
		mov r32, [r32, imm32#sc]
		mov r32, [r32, r32#sc]
	
*/

#define _LISDF_MOV_dro(_id)\
	data_set = data_src;\
	LI_IS_SET(_id)

#define _LISD_00()\
	LI_IS_DRO(ID00, _LISDF_MOV_dro);\

#define _LISDF_MOV_mio(_id)\
	data_set = data_mem;\
	LI_IS_SET(_id)

#define _LISD_01()\
	LI_IS_MIO(ID01, _LISDF_MOV_mio);\



#endif