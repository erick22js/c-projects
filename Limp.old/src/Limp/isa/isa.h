#ifndef limp_isa_h
#define limp_isa_h


/* Converts BIT SIZE with INDEX SELECTOR to register code in set operations of instruction */
#define LI_UTIL_BITINDEX2REGCODE(bit_size, index)\
	(((((4-(bit_size/8))*2)/3)<<3)|(index&0x7))


#include "../cpu/cpu.h"
#include "template/dro.h"
#include "template/uro.h"
#include "template/ido.h"
#include "template/ifo.h"
#include "template/dfr.h"
#include "template/fro.h"
#include "template/fur.h"
#include "template/mio.h"
#include "util.h"

/*
	LIMP ISA DOCS
	
	Instructions assembly types:
	
	- opc dest, src (, extra) => Do the operation from src to dest operators
	- opc opr (, extra) => Do only operation over the operator register
	- opc dest, [base (, index#sc)] (, extra) => Do operation from memory pointed by base with/without index to dest operator
	- opc (, extra) => Do operation without operators
	
	* Obs.: extra is a immediate varyable type (from 8-bit to 24-bit) additional argument, optional for instructions, is set as zero if not specified.
	
	Arguments:
	
	- r8 => Register in 8-bit set
	- r16 => Register in 16-bit set
	- r32 => Register in 32-bit set
	- reg => Any of r8, r16 or r32
	- imm8 => Immediate of 8-bit (from Current Opcode)
	- imm16 => Immeduate of 16-bit (from Current Opcode)
	- imm32 => Immediate of 32-bit (from Following Opcode)
	- imm => Any of imm8, imm16 or imm32
	- [] => Memory access of 32-bit
	
*/

#define _LISDF_NOTDEFINEDI_(_id)\
	;

#include "set/mov.h"
#include "set/mem.h"
#include "set/arithmetic.h"


/**
	SET VALUE OUTPUT RELATED
*/

#define LI_ISA_SET()\
	LI_ISA_SET_BIT(32)\
	LI_ISA_SET_BIT(16)\
	LI_ISA_SET_BIT(8)

#define LI_ISA_SET_BIT(_li_bit)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 0)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 1)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 2)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 3)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 4)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 5)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 6)\
	LI_ISA_SET_BIT_INDEX(_li_bit, 7)

#define LI_ISA_SET_BIT_INDEX(_li_bit, _li_index)\
	_JP_SET_REG##_li_bit##_##_li_index:\
		LI_CPU_setReg##_li_bit##_##_li_index(m_cpu, data_set);\
		goto *if_location;


#define LI_ISA_SETT()\
	static const void *_JP_SET[] = {\
		LI_ISA_SETT_BIT(32)\
		LI_ISA_SETT_BIT(16)\
		LI_ISA_SETT_BIT(8)\
	};

#define LI_ISA_SETT_BIT(_li_bit)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 0)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 1)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 2)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 3)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 4)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 5)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 6)\
	LI_ISA_SETT_BIT_INDEX(_li_bit, 7)

#define LI_ISA_SETT_BIT_INDEX(_li_bit, _li_index)\
	&&_JP_SET_REG##_li_bit##_##_li_index,


#define LI_ISA_SETLABEL(_li_name)\
	_JPSR_##_li_name

#define LI_IS_SET(_identifier)\
	if_location = &&LI_ISA_SETLABEL(_identifier); goto *_JP_SET[set_func]; LI_ISA_SETLABEL(_identifier):{}


/**
	GET VALUE OUTPUT RELATED
*/

#define LI_ISA_GET()\
	LI_ISA_GET_BIT_INDEX(0)\
	LI_ISA_GET_BIT_INDEX(1)\
	LI_ISA_GET_BIT_INDEX(2)\
	LI_ISA_GET_BIT_INDEX(3)\
	LI_ISA_GET_BIT_INDEX(4)\
	LI_ISA_GET_BIT_INDEX(5)\
	LI_ISA_GET_BIT_INDEX(6)\
	LI_ISA_GET_BIT_INDEX(7)\
	_JP_GET_IMM:\
		mem_index = LI_CPU_freg_getImm32(m_cpu);\
		goto *if_location;

#define LI_ISA_GET_BIT_INDEX(_li_index)\
	_JP_GET_REG_##_li_index:\
		mem_index = LI_CPU_getReg32_##_li_index(m_cpu);\
		goto *if_location;


#define LI_ISA_GETT()\
	static const void *_JP_GET[] = {\
		LI_ISA_GETT_BIT_INDEX(0)\
		LI_ISA_GETT_BIT_INDEX(1)\
		LI_ISA_GETT_BIT_INDEX(2)\
		LI_ISA_GETT_BIT_INDEX(3)\
		LI_ISA_GETT_BIT_INDEX(4)\
		LI_ISA_GETT_BIT_INDEX(5)\
		LI_ISA_GETT_BIT_INDEX(6)\
		LI_ISA_GETT_BIT_INDEX(7)\
		&&_JP_GET_IMM,\
	};

#define LI_ISA_GETT_BIT_INDEX(_li_index)\
	&&_JP_GET_REG_##_li_index,


/**
	MAIN INSTRUCTIONS EXECUTION FUNCTION
*/

void LI_ISA(LIMPCpu *m_cpu){
	
	/* Operation Registers */
	/* Input data */
	Luint32 data_src = 0;
	Luint32 data_dest = 0;
	Luint32 data_opr = 0;
	Luint32 data_mem = 0;
	Luint32 data_extra = 0;
	/* Output data */
	Luint32 data_set = 0;
	Luint32 set_func = 0;
	Luint32 mem_index = 0;
	/* Control data */
	Luint32 func = 0;
	void *if_location = 0;
	void* lif_location = 0;
	
	/* Instruction table */
	static const void* const _JP_ISA[256] = {
		&&_IS_ID00, &&_IS_ID01, &&_IS_ID02, &&_IS_ID03, &&_IS_ID04, &&_IS_ID05, &&_IS_ID06, &&_IS_ID07, &&_IS_ID08, &&_IS_ID09, &&_IS_ID0A, &&_IS_ID0B, &&_IS_ID0C, &&_IS_ID0D,
	};
	
	/* Instruction Opcode Decoding */
	goto *_JP_ISA[LI_CPU_freg_getOpcode(m_cpu)];
	
	/* SETFUNCTION */
	LI_ISA_SETT()
	LI_ISA_SET();
	
	/* GETFUNCTION */
	LI_ISA_GETT()
	LI_ISA_GET();
	
	/* FORMAT: DRO */
	LI_DROT()
	LI_DRO()
	
	/* FORMAT: URO */
	LI_UROT()
	LI_URO()
	
	/* FORMAT: IDO */
	LI_IDOT()
	LI_IDO()
	
	/* FORMAT: IFO */
	LI_IFOT()
	LI_IFO()
	
	/* FORMAT: DFR */
	LI_DFRT()
	LI_DFR()
	
	/* FORMAT: FRO */
	LI_FROT()
	LI_FRO()
	
	/* FORMAT: FUR */
	LI_FURT()
	LI_FUR()
	
	/* FORMAT: MIO */
	LI_MIOT()
	LI_MIO()
	
	_LISD_00();
	_LISD_01();
	_LISD_02();
	_LISD_03();
	_LISD_04();
	_LISD_05();
	_LISD_06();
	_LISD_07();
	_LISD_08();
	_LISD_09();
	_LISD_0A();
	_LISD_0B();
	_LISD_0C();
	_LISD_0D();
	
	/* Instruction End Execution */
	_JP_END:
	return;
}

#endif