#ifndef limp_cpu_alu_h
#define limp_cpu_alu_h

#include "../api.h"


/**
	ARITHMETIC OPERATIONS
*/

#define LI_ALU_bit(data) (LUint32(data)>>31)

#define LI_ALU_setNZO(m_cpu, _alu_result)\
	m_cpu->reg_st.nf = LI_ALU_bit(_alu_result);\
	m_cpu->reg_st.zf = _alu_result==0;\
	m_cpu->reg_st.of = _alu_result&1;\

#define LI_ALU_ADD(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1+opr2;\
		m_cpu->reg_st.cf = (_alu_result<opr1)&&(_alu_result<opr2);\
		m_cpu->reg_st.vf = ((LI_ALU_bit(opr1)==LI_ALU_bit(opr2))&(LI_ALU_bit(_alu_result)==(LI_ALU_bit(opr1)^1)));\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_ADC(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1+opr2+m_cpu->reg_st.cf;\
		m_cpu->reg_st.cf = (_alu_result<opr1)&&(_alu_result<opr2);\
		m_cpu->reg_st.vf = ((LI_ALU_bit(opr1)==LI_ALU_bit(opr2))&(LI_ALU_bit(_alu_result)==(LI_ALU_bit(opr1)^1)));\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SUB(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1-opr2;\
		m_cpu->reg_st.bf = _alu_result>opr1;\
		m_cpu->reg_st.vf = ((LI_ALU_bit(opr1)!=LI_ALU_bit(opr2))&(LI_ALU_bit(_alu_result)==LI_ALU_bit(opr2)));\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SBB(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1-opr2-m_cpu->reg_st.bf;\
		m_cpu->reg_st.bf = _alu_result>opr1;\
		m_cpu->reg_st.vf = ((LI_ALU_bit(opr1)!=LI_ALU_bit(opr2))&(LI_ALU_bit(_alu_result)==LI_ALU_bit(opr2)));\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = opr1-opr2;\
	}

#define LI_ALU_MUL(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1*opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_DIV(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1/opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_MOD(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1%opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_AND(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1&opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_OR(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1|opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_XOR(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1^opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_NOT(m_cpu, opr1, out_opr){\
		Luint32 _alu_result = ~opr1;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SHL(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1<<opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SHR(m_cpu, opr1, opr2, out_opr){\
		Luint32 _alu_result = opr1>>opr2;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SAL(m_cpu, opr1, opr2, out_opr){\
		Luint32 opr1_signal = LI_ALU_bit(opr1);\
		Luint32 _alu_result = opr1<<opr2;\
		_alu_result *= opr1_signal?-1:1;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_SAR(m_cpu, opr1, opr2, out_opr){\
		Luint32 opr1_signal = LI_ALU_bit(opr1);\
		Luint32 _alu_result = (opr1&0x7fffffff)>>opr2;\
		_alu_result *= opr1_signal?-1:1;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_RTL(m_cpu, opr1, opr2, out_opr){\
		Luint32 shifting = (opr2)&0x1f;\
		Luint32 upper = opr1<<shifting;\
		Luint32 lower = opr1>>(32-shifting);\
		Luint32 _alu_result = upper|lower;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}

#define LI_ALU_RTR(m_cpu, opr1, opr2, out_opr){\
		Luint32 shifting = (opr2)&0x1f;\
		Luint32 upper = opr1<<(32-shifting);\
		Luint32 lower = opr1>>shifting;\
		Luint32 _alu_result = upper|lower;\
		LI_ALU_setNZO(m_cpu, _alu_result)\
		out_opr = _alu_result;\
	}


/**
	CONDITION TEST OPERATIONS
*/

#define LI_ALU_COND_EQ(m_cpu, opr1, opr2)\
	(LUint32(opr1)==LUint32(opr2))

#define LI_ALU_COND_NE(m_cpu, opr1, opr2)\
	(LUint32(opr1)!=LUint32(opr2))

#define LI_ALU_COND_LT(m_cpu, opr1, opr2)\
	(LSint32(opr1)<LSint32(opr2))

#define LI_ALU_COND_GT(m_cpu, opr1, opr2)\
	(LSint32(opr1)<LSint32(opr2))

#define LI_ALU_COND_LE(m_cpu, opr1, opr2)\
	(LSint32(opr1)<=LSint32(opr2))

#define LI_ALU_COND_GE(m_cpu, opr1, opr2)\
	(LSint32(opr1)>=LSint32(opr2))

#define LI_ALU_COND_BL(m_cpu, opr1, opr2)\
	(LUint32(opr1)<LUint32(opr2))

#define LI_ALU_COND_AB(m_cpu, opr1, opr2)\
	(LUint32(opr1)>LUint32(opr2))

#define LI_ALU_COND_BE(m_cpu, opr1, opr2)\
	(LUint32(opr1)<=LUint32(opr2))

#define LI_ALU_COND_AE(m_cpu, opr1, opr2)\
	(LUint32(opr1)>=LUint32(opr2))

#define LI_ALU_COND_EZ(m_cpu, opr1)\
	(LUint32(opr1)==0)

#define LI_ALU_COND_NZ(m_cpu, opr1)\
	(LUint32(opr1)!=0)

#define LI_ALU_COND_LTZ(m_cpu, opr1)\
	(LSint32(opr1)<0)

#define LI_ALU_COND_GTZ(m_cpu, opr1)\
	(LSint32(opr1)>0)

#define LI_ALU_COND_LEZ(m_cpu, opr1)\
	(LSint32(opr1)<=0)

#define LI_ALU_COND_GEZ(m_cpu, opr1)\
	(LSint32(opr1)>=0)

/* EQ */
#define LI_ALU_COND_SZ(m_cpu)\
	(m_cpu->reg_st.zf)

#define LI_ALU_COND_S_EQ(m_cpu) LI_ALU_COND_SZ(m_cpu)

/* NE */
#define LI_ALU_COND_CZ(m_cpu)\
	(!m_cpu->reg_st.zf)

#define LI_ALU_COND_S_NE(m_cpu) LI_ALU_COND_CZ(m_cpu)

/* LT */
#define LI_ALU_COND_NEVN(m_cpu)\
	(m_cpu->reg_st.vf!=m_cpu->reg_st.nf)

#define LI_ALU_COND_S_LT(m_cpu) LI_ALU_COND_NEVN(m_cpu)

/* GT */
#define LI_ALU_COND_EQVN(m_cpu)\
	(m_cpu->reg_st.vf==m_cpu->reg_st.nf)

#define LI_ALU_COND_S_GT(m_cpu) LI_ALU_COND_EQVN(m_cpu)

/* LE */
#define LI_ALU_COND_NEVNOSZ(m_cpu)\
	((m_cpu->reg_st.vf!=m_cpu->reg_st.nf)|(m_cpu->reg_st.zf))

#define LI_ALU_COND_S_LE(m_cpu) LI_ALU_COND_NEVNOSZ(m_cpu)

/* GE */
#define LI_ALU_COND_EQVNOSZ(m_cpu)\
	((m_cpu->reg_st.vf==m_cpu->reg_st.nf)|(m_cpu->reg_st.zf))

#define LI_ALU_COND_S_GE(m_cpu) LI_ALU_COND_EQVNOSZ(m_cpu)

/* BL */
#define LI_ALU_COND_SB(m_cpu)\
	(m_cpu->reg_st.bf)

#define LI_ALU_COND_S_BL(m_cpu) LI_ALU_COND_SB(m_cpu)

/* AB */
#define LI_ALU_COND_CB(m_cpu)\
	(!m_cpu->reg_st.bf)

#define LI_ALU_COND_S_AB(m_cpu) LI_ALU_COND_CB(m_cpu)

/* BE */
#define LI_ALU_COND_SBOSZ(m_cpu)\
	((m_cpu->reg_st.bf)|(m_cpu->reg_st.zf))

#define LI_ALU_COND_S_BE(m_cpu) LI_ALU_COND_SBOSZ(m_cpu)

/* AE */
#define LI_ALU_COND_CBOSZ(m_cpu)\
	((!m_cpu->reg_st.bf)|(m_cpu->reg_st.zf))

#define LI_ALU_COND_S_AE(m_cpu) LI_ALU_COND_CBOSZ(m_cpu)

#define LI_ALU_COND_SV(m_cpu)\
	(m_cpu->reg_st.vf)

#define LI_ALU_COND_CV(m_cpu)\
	(!m_cpu->reg_st.vf)

#define LI_ALU_COND_SC(m_cpu)\
	(m_cpu->reg_st.cf)

#define LI_ALU_COND_CC(m_cpu)\
	(!m_cpu->reg_st.cf)

#define LI_ALU_COND_SO(m_cpu)\
	(m_cpu->reg_st.of)

#define LI_ALU_COND_CO(m_cpu)\
	(!m_cpu->reg_st.of)


#endif
