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
#include "set/flow.h"


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

/* Invalid instruction opcode */
#define LI_IS_INVI(_id)\
	goto _JP_INVI;

/* Invalid instruction argument */
#define LI_IS_INVA(_id)\
	goto _JP_INVI;

void LI_ISA(LIMPCpu *m_cpu);

#endif
