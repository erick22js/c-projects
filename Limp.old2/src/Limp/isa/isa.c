#include "isa.h"

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
		&&_IS_ID00, &&_IS_ID01, &&_IS_ID02, &&_IS_ID03, &&_IS_ID04, &&_IS_ID05, &&_IS_ID06, &&_IS_ID07,
		&&_IS_ID08, &&_IS_ID09, &&_IS_ID0A, &&_IS_ID0B, &&_IS_ID0C, &&_IS_ID0D, &&_IS_ID0E, &&_IS_ID0F,
		&&_IS_ID10, &&_IS_ID11,
		&&_IS_ID12, &&_IS_ID13, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
		&&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI, &&_JP_INVI,
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
	
	/* INVALID INSTRUCTION */
	_JP_INVI:
		
	goto _JP_END;
	/* INVALID INSTRUCTION ARGUMENT */
	_JP_INVA:
		
	goto _JP_INVI;
	
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
	_LISD_0E();
	_LISD_0F();
	_LISD_10();
	_LISD_11();
	_LISD_12();
	_LISD_13();
	
	/* Instruction End Execution */
	_JP_END:
	return;
}
