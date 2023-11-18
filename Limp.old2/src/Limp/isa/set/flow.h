#ifndef limp_isaset_flow_h
#define limp_isaset_flow_h

#include "../template/ido.h"
#include "../../cpu/alu.h"


/**
		JMP
	
	Jumps to a Absolute Address
	
	# IDO: 0E
		jmp imm<2
	
	# FRO: 0F
		jmp imm32
		jmp r32
	
*/

#define _LISDF_JMP_ido(_id)\
	LIMP_CPU_jumpAbs(m_cpu, data_extra<<2);

#define _LISD_0E()\
	LI_IS_IDO(ID0E, _LISDF_JMP_ido);\

#define _LISDF_JMP_fro_00(_id)\
	LIMP_CPU_jumpAbs(m_cpu, LI_CPU_freg_getImm32(m_cpu));

#define _LISDF_JMP_fro_01(_id)\
	LIMP_CPU_jumpAbs(m_cpu, data_dest);

			
/**
		JMPR
	
	Jumps by a Relative Address
	
	# IDO: 10
		jmpr imm<2
	
	# FRO: 0F
		jmp imm32
		jmp r32
	
*/

#define _LISDF_JMPR_ido(_id)\
	LIMP_CPU_jumpRel(m_cpu, L24T32(data_extra)<<2);

#define _LISD_10()\
	LI_IS_IDO(ID10, _LISDF_JMPR_ido);\

#define _LISDF_JMPR_fro_02(_id)\
	LIMP_CPU_jumpRel(m_cpu, LI_CPU_freg_getImm32(m_cpu));

#define _LISDF_JMPR_fro_03(_id)\
	LIMP_CPU_jumpRel(m_cpu, data_dest);

#define _LISD_0F()\
	LI_IS_FRO(ID0F,\
			_LISDF_JMP_fro_00, _LISDF_JMP_fro_01,\
			_LISDF_JMPR_fro_02, _LISDF_JMPR_fro_03,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI,\
			LI_IS_INVI, LI_IS_INVI, LI_IS_INVI, LI_IS_INVI\
			);\


/**
		JR
	
	Jumps by a Relative Offset Conditionally
	
	# FUR: 11
		00: jeq imm<2, r32
		01: jne imm<2, r32
		02: jlt imm<2, r32
		03: jgt imm<2, r32
		04: jle imm<2, r32
		05: jge imm<2, r32
		06: jbl imm<2, r32
		07: jab imm<2, r32
		08: jbe imm<2, r32
		09: jae imm<2, r32
		10: jez imm<2, r32
		11: jnz imm<2, r32
		12: jltz imm<2, r32
		13: jgtz imm<2, r32
		14: jlez imm<2, r32
		15: jgez imm<2, r32
		16: jeq imm<2
		17: jne imm<2
		18: jlt imm<2
		19: jgt imm<2
		20: jle imm<2
		21: jge imm<2
		22: jbl imm<2
		23: jab imm<2
		24: jbe imm<2
		25: jae imm<2
		26: jsv imm<2
		27: jcv imm<2
		28: jsc imm<2
		29: jcc imm<2
		30: jso imm<2
		31: jco imm<2
	
*/

#define _LISDF_JR_fur_00(_id)\
	if(LI_ALU_COND_EQ(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_01(_id)\
	if(LI_ALU_COND_NE(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_02(_id)\
	if(LI_ALU_COND_LT(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_03(_id)\
	if(LI_ALU_COND_GT(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_04(_id)\
	if(LI_ALU_COND_LE(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_05(_id)\
	if(LI_ALU_COND_GE(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_06(_id)\
	if(LI_ALU_COND_BL(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_07(_id)\
	if(LI_ALU_COND_AB(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_08(_id)\
	if(LI_ALU_COND_BE(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_09(_id)\
	if(LI_ALU_COND_AE(m_cpu, data_opr, LIMP_CPU_getReg_EDX(m_cpu))){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_10(_id)\
	if(LI_ALU_COND_EZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_11(_id)\
	if(LI_ALU_COND_NZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_12(_id)\
	if(LI_ALU_COND_LTZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_13(_id)\
	if(LI_ALU_COND_GTZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_14(_id)\
	if(LI_ALU_COND_LEZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_15(_id)\
	if(LI_ALU_COND_GEZ(m_cpu, data_opr)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_16(_id)\
	if(LI_ALU_COND_S_EQ(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_17(_id)\
	if(LI_ALU_COND_S_NE(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_18(_id)\
	if(LI_ALU_COND_S_LT(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_19(_id)\
	if(LI_ALU_COND_S_GT(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_20(_id)\
	if(LI_ALU_COND_S_LE(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_21(_id)\
	if(LI_ALU_COND_S_GE(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_22(_id)\
	if(LI_ALU_COND_S_BL(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_23(_id)\
	if(LI_ALU_COND_S_AB(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_24(_id)\
	if(LI_ALU_COND_S_BE(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_25(_id)\
	if(LI_ALU_COND_S_AE(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_26(_id)\
	if(LI_ALU_COND_SV(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_27(_id)\
	if(LI_ALU_COND_CV(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_28(_id)\
	if(LI_ALU_COND_SC(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_29(_id)\
	if(LI_ALU_COND_CC(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_30(_id)\
	if(LI_ALU_COND_SO(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISDF_JR_fur_31(_id)\
	if(LI_ALU_COND_CO(m_cpu)){\
		LIMP_CPU_jumpRel(m_cpu, L16T32(data_extra)<<2);\
	}

#define _LISD_11()\
	LI_IS_FUR(ID11, \
		_LISDF_JR_fur_00, _LISDF_JR_fur_01,\
		_LISDF_JR_fur_02, _LISDF_JR_fur_03,\
		_LISDF_JR_fur_04, _LISDF_JR_fur_05,\
		_LISDF_JR_fur_06, _LISDF_JR_fur_07,\
		_LISDF_JR_fur_08, _LISDF_JR_fur_09,\
		_LISDF_JR_fur_10, _LISDF_JR_fur_11,\
		_LISDF_JR_fur_12, _LISDF_JR_fur_13,\
		_LISDF_JR_fur_14, _LISDF_JR_fur_15,\
		_LISDF_JR_fur_16, _LISDF_JR_fur_17,\
		_LISDF_JR_fur_18, _LISDF_JR_fur_19,\
		_LISDF_JR_fur_20, _LISDF_JR_fur_21,\
		_LISDF_JR_fur_22, _LISDF_JR_fur_23,\
		_LISDF_JR_fur_24, _LISDF_JR_fur_25,\
		_LISDF_JR_fur_26, _LISDF_JR_fur_27,\
		_LISDF_JR_fur_28, _LISDF_JR_fur_29,\
		_LISDF_JR_fur_30, _LISDF_JR_fur_31\
		);




#endif
