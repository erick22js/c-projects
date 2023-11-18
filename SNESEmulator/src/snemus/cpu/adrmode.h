#ifndef snemus_cpu_adrmode_h
#define snemus_cpu_adrmode_h

#include "../api.h"


typedef enum SMAdrm{
	ADRM_NONE,
	ADRM_ABSOLUTEDBR,
	ADRM_ABSOLUTEPBR,
	ADRM_ABSOLUTE_X_INDEXED,
	ADRM_ABSOLUTE_Y_INDEXED,
	ADRM_ABSOLUTE_INDEXED_INDIRECT,
	ADRM_ABSOLUTE_INDIRECT,
	ADRM_ABSOLUTE_INDIRECT_LONG,
	ADRM_ABSOLUTE_LONG,
	ADRM_ABSOLUTE_LONG_X_INDEXED,
	ADRM_ACUMULATOR,
	ADRM_BLOCKMOVE,
	ADRM_DIRECTPAGE,
	ADRM_DIRECTPAGE_X_INDEXED,
	ADRM_DIRECTPAGE_Y_INDEXED,
	ADRM_DIRECTPAGE_X_INDEXED_INDIRECT,
	ADRM_DIRECTPAGE_INDIRECT,
	ADRM_DIRECTPAGE_INDIRECT_LONG,
	ADRM_DIRECTPAGE_INDIRECT_Y_INDEXED,
	ADRM_DIRECTPAGE_INDIRECT_LONG_Y_INDEXED,
	ADRM_IMMEDIATEACU,
	ADRM_IMMEDIATEMEM,
	ADRM_IMMEDIATEINDEX,
	ADRM_IMPLIED,
	ADRM_PROGRAMCOUNTER_RELATIVE,
	ADRM_PROGRAMCOUNTER_RELATIVE_LONG,
	ADRM_STACKPOINTER_ABSOLUTE,
	ADRM_STACKPOINTER_DIRECTPAGE_INDIRECT,
	ADRM_STACKPOINTER_INTERRUPT,
	ADRM_STACKPOINTER_PROGRAMCOUNTER_RELATIVE,
	ADRM_STACKPOINTER_PULL,
	ADRM_STACKPOINTER_PUSH,
	ADRM_STACKPOINTER_RTI,
	ADRM_STACKPOINTER_RTL,
	ADRM_STACKPOINTER_RTS,
	ADRM_STACKPOINTER_RELATIVE,
	ADRM_STACKPOINTER_RELATIVE_INDIRECT_Y_INDEXED,
	ADRM_TOTAL,
	
}SMAdrm;

typedef enum SMAdrmMod{
	ADRMOD_READMEM = 0x0001,
	ADRMOD_DPLOBYTE = 0x0002,
}SMAdrmMod;


#include "cpu.h"


void SM_AdrMode_None(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteDBR(SMCpu *m_cpu);
void SM_AdrMode_AbsolutePBR(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteXIndexed(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteYIndexed(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteIndexedIndirect(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteIndirect(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteIndirectLong(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteLong(SMCpu *m_cpu);
void SM_AdrMode_AbsoluteLongXIndexed(SMCpu *m_cpu);
void SM_AdrMode_Acumulator(SMCpu *m_cpu);
void SM_AdrMode_BlockMove(SMCpu *m_cpu);
void SM_AdrMode_Directpage(SMCpu *m_cpu);
void SM_AdrMode_DirectpageXIndexed(SMCpu *m_cpu);
void SM_AdrMode_DirectpageYIndexed(SMCpu *m_cpu);
void SM_AdrMode_DirectpageXIndexedIndirect(SMCpu *m_cpu);
void SM_AdrMode_DirectpageIndirect(SMCpu *m_cpu);
void SM_AdrMode_DirectpageIndirectLong(SMCpu *m_cpu);
void SM_AdrMode_DirectpageIndirectYIndexed(SMCpu *m_cpu);
void SM_AdrMode_DirectpageIndirectLongYIndexed(SMCpu *m_cpu);
void SM_AdrMode_ImmediateAcu(SMCpu *m_cpu);
void SM_AdrMode_ImmediateMem(SMCpu *m_cpu);
void SM_AdrMode_ImmediateIndex(SMCpu *m_cpu);
void SM_AdrMode_Implied(SMCpu *m_cpu);
void SM_AdrMode_ProgramcounterRelative(SMCpu *m_cpu);
void SM_AdrMode_ProgramcounterRelativeLong(SMCpu *m_cpu);
void SM_AdrMode_StackpointerAbsolute(SMCpu *m_cpu);
void SM_AdrMode_StackpointerDirectpageIndirect(SMCpu *m_cpu);
void SM_AdrMode_StackpointerInterrupt(SMCpu *m_cpu);
void SM_AdrMode_StackpointerProgramcounterRelative(SMCpu *m_cpu);
void SM_AdrMode_StackpointerPull(SMCpu *m_cpu);
void SM_AdrMode_StackpointerPush(SMCpu *m_cpu);
void SM_AdrMode_StackpointerRti(SMCpu *m_cpu);
void SM_AdrMode_StackpointerRtl(SMCpu *m_cpu);
void SM_AdrMode_StackpointerRts(SMCpu *m_cpu);
void SM_AdrMode_StackpointerRelative(SMCpu *m_cpu);
void SM_AdrMode_StackpointerRelativeIndirectYIndexed(SMCpu *m_cpu);

void SM_AdrModePrint_None(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteDBR(SMCpu *m_cpu);
void SM_AdrModePrint_AbsolutePBR(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteXIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteYIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteIndexedIndirect(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteIndirect(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteIndirectLong(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteLong(SMCpu *m_cpu);
void SM_AdrModePrint_AbsoluteLongXIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_Acumulator(SMCpu *m_cpu);
void SM_AdrModePrint_BlockMove(SMCpu *m_cpu);
void SM_AdrModePrint_Directpage(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageXIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageYIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageXIndexedIndirect(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageIndirect(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageIndirectLong(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageIndirectYIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_DirectpageIndirectLongYIndexed(SMCpu *m_cpu);
void SM_AdrModePrint_ImmediateAcu(SMCpu *m_cpu);
void SM_AdrModePrint_ImmediateMem(SMCpu *m_cpu);
void SM_AdrModePrint_ImmediateIndex(SMCpu *m_cpu);
void SM_AdrModePrint_Implied(SMCpu *m_cpu);
void SM_AdrModePrint_ProgramcounterRelative(SMCpu *m_cpu);
void SM_AdrModePrint_ProgramcounterRelativeLong(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerAbsolute(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerDirectpageIndirect(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerInterrupt(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerProgramcounterRelative(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerPull(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerPush(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerRti(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerRtl(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerRts(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerRelative(SMCpu *m_cpu);
void SM_AdrModePrint_StackpointerRelativeIndirectYIndexed(SMCpu *m_cpu);


typedef struct SMAdrMode{
	void (*adrmfunc)(SMCpu *m_cpu);
	void (*adrmpfunc)(SMCpu *m_cpu);
}SMAdrMode;


extern SMAdrMode sm_adrmodes[ADRM_TOTAL];


#endif // snemus_cpu_adrmode
