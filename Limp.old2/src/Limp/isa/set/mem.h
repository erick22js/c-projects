#ifndef limp_isaset_mem_h
#define limp_isaset_mem_h

#include "../template/dro.h"
#include "../template/mio.h"

/**
		STR
	
	Stores a value from operand source to the memory address.
	
	# DRO: 02
		strd reg, reg (, imm16)
		strd imm32, reg (, imm16)
		strd imm16, reg (, imm16)
	
	# FUR: 03
		00: strd r32, imm16, EBX
		01: strd r32, imm16, ECX
		02: strd r32, imm32 (, imm16)
		03: strd r32, imm32, EBX
		04: strd r32, imm32, ECX
		05: strd r32, EAX, ECX
		06: strd r32, EAX, imm32
		07: strd r32, EDX, imm32
		08: strd EBX, r32, imm32
		09: strd imm32, r32
		10: strw r32, imm16
		11: strw r32, AX (, imm16)
		12: strw r32, BX (, imm16)
		13: strw r32, CX (, imm16)
		14: strw r32, DX (, imm16)
		15: strw r32, imm16, EBX
		16: strw r32, imm16, ECX
		17: strw imm32, imm16
		18: strw imm32, r32/16
		19: strw EBX, r32/16 (, imm16)
		20: strw EBX, r32/16, ECX
		21: strb r32, imm8
		22: strb r32, AL (, imm16)
		23: strb r32, AH (, imm16)
		24: strb r32, DL (, imm16)
		25: strb r32, DH (, imm16)
		26: strb r32, imm8, EBX
		27: strb r32, imm8, ECX
		28: strb imm32, imm8
		29: strb imm32, AL
		30: strb EBX, AL (, imm16)
		31: strb EBX, AL, ECX
	
*/

#define _LISDF_STR_dro(_id)\
	Luint32 effective_address = data_src+L16T32(data_extra);\
	LIMP_CPU_setMem32(m_cpu, effective_address, data_dest);

#define _LISD_02()\
	LI_IS_DRO(ID02, _LISDF_STR_dro);

#define _LISDF_STR_fur_00(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_EBX(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_01(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_02(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LI_CPU_freg_getImm32(m_cpu));

#define _LISDF_STR_fur_03(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_EBX(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LI_CPU_freg_getImm32(m_cpu));

#define _LISDF_STR_fur_04(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LI_CPU_freg_getImm32(m_cpu));

#define _LISDF_STR_fur_05(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LIMP_CPU_getReg_EAX(m_cpu));

#define _LISDF_STR_fur_06(_id)\
	Luint32 effective_address = data_opr+LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LIMP_CPU_getReg_EAX(m_cpu));

#define _LISDF_STR_fur_07(_id)\
	Luint32 effective_address = data_opr+LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, LIMP_CPU_getReg_EDX(m_cpu));

#define _LISDF_STR_fur_08(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, data_opr);

#define _LISDF_STR_fur_09(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem32(m_cpu, effective_address, data_opr);

#define _LISDF_STR_fur_10(_id)\
	Luint32 effective_address = data_opr;\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_11(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem16(m_cpu, effective_address, LIMP_CPU_getReg_AX(m_cpu));

#define _LISDF_STR_fur_12(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem16(m_cpu, effective_address, LIMP_CPU_getReg_BX(m_cpu));

#define _LISDF_STR_fur_13(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem16(m_cpu, effective_address, LIMP_CPU_getReg_CX(m_cpu));

#define _LISDF_STR_fur_14(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem16(m_cpu, effective_address, LIMP_CPU_getReg_DX(m_cpu));

#define _LISDF_STR_fur_15(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_BX(m_cpu);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_16(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_CX(m_cpu);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_17(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_18(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_opr);

#define _LISDF_STR_fur_19(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_opr);

#define _LISDF_STR_fur_20(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_setMem16(m_cpu, effective_address, data_opr);

#define _LISDF_STR_fur_21(_id)\
	Luint32 effective_address = data_opr;\
	LIMP_CPU_setMem8(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_22(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_AL(m_cpu));

#define _LISDF_STR_fur_23(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_AH(m_cpu));

#define _LISDF_STR_fur_24(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_DL(m_cpu));

#define _LISDF_STR_fur_25(_id)\
	Luint32 effective_address = data_opr+L16T32(data_extra);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_DH(m_cpu));

#define _LISDF_STR_fur_26(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_BX(m_cpu);\
	LIMP_CPU_setMem8(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_27(_id)\
	Luint32 effective_address = data_opr+LIMP_CPU_getReg_CX(m_cpu);\
	LIMP_CPU_setMem8(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_28(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem8(m_cpu, effective_address, data_extra);

#define _LISDF_STR_fur_29(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_AL(m_cpu));

#define _LISDF_STR_fur_30(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_AL(m_cpu));

#define _LISDF_STR_fur_31(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_setMem8(m_cpu, effective_address, LIMP_CPU_getReg_AL(m_cpu));

#define _LISD_03()\
	LI_IS_FUR(ID03, \
		_LISDF_STR_fur_00, _LISDF_STR_fur_01,\
		_LISDF_STR_fur_02, _LISDF_STR_fur_03,\
		_LISDF_STR_fur_04, _LISDF_STR_fur_05,\
		_LISDF_STR_fur_06, _LISDF_STR_fur_07,\
		_LISDF_STR_fur_08, _LISDF_STR_fur_09,\
		_LISDF_STR_fur_10, _LISDF_STR_fur_11,\
		_LISDF_STR_fur_12, _LISDF_STR_fur_13,\
		_LISDF_STR_fur_14, _LISDF_STR_fur_15,\
		_LISDF_STR_fur_16, _LISDF_STR_fur_17,\
		_LISDF_STR_fur_18, _LISDF_STR_fur_19,\
		_LISDF_STR_fur_20, _LISDF_STR_fur_21,\
		_LISDF_STR_fur_22, _LISDF_STR_fur_23,\
		_LISDF_STR_fur_24, _LISDF_STR_fur_25,\
		_LISDF_STR_fur_26, _LISDF_STR_fur_27,\
		_LISDF_STR_fur_28, _LISDF_STR_fur_29,\
		_LISDF_STR_fur_30, _LISDF_STR_fur_31\
		);

/**
		LDM
	
	Loads a value from memory address to register operand.
	
	# DRO: 04
		ldmd reg, reg (, imm16)
		ldmd reg, imm32 (, imm16)
		ldmd reg, imm16 (, imm16)
	
	# FUR: 05
		00: ldmw r16, EBX (, imm16)
		01: ldmw r16, EBX, ECX
		02: ldmw r16, ESP (, imm16)
		03: ldmw r16, EFP (, imm16)
		04: ldmw r16, imm32
		05: ldmw r16, EBX, imm32
		06: ldmw r16, ESP, imm32
		07: ldmw r16, EFP, imm32
		08: ldmb r8, EBX (, imm16)
		09: ldmb r8, EBX, ECX
		10: ldmb r8, ESP (, imm16)
		11: ldmb r8, EFP (, imm16)
		12: ldmb r8, imm32
		13: ldmb r8, EBX, imm32
		14: ldmb r8, ESP, imm32
		15: ldmb r8, EFP, imm32
		16: ldmd r32, EBX, imm32
		17: ldmd r32, EBX, ECX

*/

#define _LISDF_LDM_dro(_id)\
	Luint32 effective_address = data_src+L16T32(data_extra);\
	LIMP_CPU_getMem32(m_cpu, effective_address, data_set);\
	LI_IS_SET(_id);

#define _LISD_04()\
	LI_IS_DRO(ID04, _LISDF_LDM_dro);

#define _LISDF_LDM_fur_00(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_01(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_02(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_ESP(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_03(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EFP(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_04(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_05(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_EBX(m_cpu);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_06(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_ESP(m_cpu);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_07(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_EFP(m_cpu);\
	LIMP_CPU_getMem16(m_cpu, effective_address, data_set);\
	set_func = 8|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_08(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_09(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_10(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_ESP(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_11(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EFP(m_cpu)+L16T32(data_extra);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_12(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_13(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_EBX(m_cpu);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_14(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_ESP(m_cpu);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_15(_id)\
	Luint32 effective_address = LI_CPU_freg_getImm32(m_cpu)+LIMP_CPU_getReg_EFP(m_cpu);\
	LIMP_CPU_getMem8(m_cpu, effective_address, data_set);\
	set_func = 16|LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_16(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LI_CPU_freg_getImm32(m_cpu);\
	LIMP_CPU_getMem32(m_cpu, effective_address, data_set);\
	set_func = LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISDF_LDM_fur_17(_id)\
	Luint32 effective_address = LIMP_CPU_getReg_EBX(m_cpu)+LIMP_CPU_getReg_ECX(m_cpu);\
	LIMP_CPU_getMem32(m_cpu, effective_address, data_set);\
	set_func = LI_CPU_freg_getFUR_rego(m_cpu);\
	LI_IS_SET(_id);

#define _LISD_05()\
	LI_IS_FUR(ID05, \
		_LISDF_LDM_fur_00, _LISDF_LDM_fur_01,\
		_LISDF_LDM_fur_02, _LISDF_LDM_fur_03,\
		_LISDF_LDM_fur_04, _LISDF_LDM_fur_05,\
		_LISDF_LDM_fur_06, _LISDF_LDM_fur_07,\
		_LISDF_LDM_fur_08, _LISDF_LDM_fur_09,\
		_LISDF_LDM_fur_10, _LISDF_LDM_fur_11,\
		_LISDF_LDM_fur_12, _LISDF_LDM_fur_13,\
		_LISDF_LDM_fur_14, _LISDF_LDM_fur_15,\
		_LISDF_LDM_fur_16, _LISDF_LDM_fur_17,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_,\
		_LISDF_NOTDEFINEDI_, _LISDF_NOTDEFINEDI_\
	)




#endif