#include <stdio.h>

#include "cpu.h"
#include "../emulation.h"


void SM_AdrMode_None(SMCpu *m_cpu){
	/* FOR NOT IMPLEMENTED FUNCTION */
	NOT_IMPLEMENTED("ADDRESSING MODE");
}

void SM_AdrMode_AbsoluteDBR(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), m_cpu->reg_dbr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_AbsolutePBR(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), m_cpu->reg_pbr);
}

void SM_AdrMode_AbsoluteXIndexed(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), m_cpu->reg_dbr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			m_cpu->arg_effectiveAdr += m_cpu->reg_x;
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_x);
		}
		
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	else{
		Uint8 lastbank = aBank(m_cpu->arg_effectiveAdr);
		
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			m_cpu->arg_effectiveAdr += m_cpu->reg_x;
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_x);
		}
		
		/* Adding Index Cross the Boundary */
		if(lastbank!=(aBank(m_cpu->arg_effectiveAdr))){
			SM_Emu_emuCycles(m_cpu, 1);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_AbsoluteYIndexed(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), m_cpu->reg_dbr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			m_cpu->arg_effectiveAdr += m_cpu->reg_y;
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
		}
		
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	else{
		Uint8 lastbank = aBank(m_cpu->arg_effectiveAdr);
		
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			m_cpu->arg_effectiveAdr += m_cpu->reg_y;
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
		}
		
		/* Adding Index Cross the Boundary */
		if(lastbank!=(aBank(m_cpu->arg_effectiveAdr))){
			SM_Emu_emuCycles(m_cpu, 1);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_AbsoluteIndexedIndirect(SMCpu *m_cpu){
	Uint16 indirect_address = SM_Cpu_fetch16(m_cpu);
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		indirect_address += m_cpu->reg_x;
	}
	/* 8-bit mode */
	else{
		indirect_address += toU8(m_cpu->reg_x);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, m_cpu->reg_pbr), m_cpu->reg_pbr);
}

void SM_AdrMode_AbsoluteIndirect(SMCpu *m_cpu){
	Uint16 indirect_address = SM_Cpu_fetch16(m_cpu);
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), m_cpu->reg_pbr);
}

void SM_AdrMode_AbsoluteIndirectLong(SMCpu *m_cpu){
	Uint16 indirect_address = SM_Cpu_fetch16(m_cpu);
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), SM_Cpu_readMem8(m_cpu, indirect_address+2, 0x00));
}

void SM_AdrMode_AbsoluteLong(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), SM_Cpu_fetch8(m_cpu));
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_AbsoluteLongXIndexed(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_fetch16(m_cpu), SM_Cpu_fetch8(m_cpu));
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_x;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_x);
	}
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_Acumulator(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->arg_data = m_cpu->reg_acu;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_data = toU8(m_cpu->reg_acu);
	}
}

void SM_AdrMode_BlockMove(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_BlockMove");
}

/* OBS: Adds one cycle on addressing mode with direct page if this is different from zero */
void SM_AdrMode_Directpage(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toU16(m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu));
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageXIndexed(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_x;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_x);
	}
	
	m_cpu->arg_effectiveAdr = toU16(m_cpu->arg_effectiveAdr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageYIndexed(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_y;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
	}
	
	m_cpu->arg_effectiveAdr = toU16(m_cpu->arg_effectiveAdr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageXIndexedIndirect(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		indirect_address += m_cpu->reg_x;
	}
	/* 8-bit mode */
	else{
		indirect_address += toU8(m_cpu->reg_x);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), m_cpu->reg_dbr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageIndirect(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), m_cpu->reg_dbr);
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageIndirectLong(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), SM_Cpu_readMem8(m_cpu, indirect_address+2, 0x00));
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageIndirectYIndexed(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), m_cpu->reg_dbr);
	
	Uint8 oldbank = aBank(m_cpu->arg_effectiveAdr);
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_y;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
	}
	
	if(oldbank!=aBank(m_cpu->arg_effectiveAdr)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_DirectpageIndirectLongYIndexed(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_dp+SM_Cpu_fetch8(m_cpu);
	
	/* If DP!=0, run 1 cycle */
	Uint16 reg_dp = m_cpu->arg_mod&ADRMOD_DPLOBYTE?m_cpu->reg_dp&0xff:m_cpu->reg_dp;
	if(reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), SM_Cpu_readMem8(m_cpu, indirect_address+2, 0x00));
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_y;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
	}
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_ImmediateAcu(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = m_cpu->reg_pc;
	
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->arg_data = SM_Cpu_fetch16(m_cpu);
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_data = SM_Cpu_fetch8(m_cpu);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_ImmediateMem(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = m_cpu->reg_pc;
	
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		m_cpu->arg_data = SM_Cpu_fetch16(m_cpu);
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_data = SM_Cpu_fetch8(m_cpu);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_ImmediateIndex(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = m_cpu->reg_pc;
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_data = SM_Cpu_fetch16(m_cpu);
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_data = SM_Cpu_fetch8(m_cpu);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_X)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_Implied(SMCpu *m_cpu){}



void SM_AdrMode_ProgramcounterRelative(SMCpu *m_cpu){
	Uint32 adrsum = toS8(SM_Cpu_fetch8(m_cpu))+m_cpu->reg_pc;
	m_cpu->arg_effectiveAdr = toU16(adrsum);
	m_cpu->arg_effectiveAdr = toAddress(m_cpu->arg_effectiveAdr, m_cpu->reg_pbr);
	m_cpu->arg_pcCrossBoundary = (adrsum>>16)!=0;
}

void SM_AdrMode_ProgramcounterRelativeLong(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toU16(SM_Cpu_fetch16(m_cpu)+m_cpu->reg_pc);
	m_cpu->arg_effectiveAdr = toAddress(m_cpu->arg_effectiveAdr, m_cpu->reg_pbr);
}

void SM_AdrMode_StackpointerAbsolute(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerAbsolute");
}

void SM_AdrMode_StackpointerDirectpageIndirect(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerDirectpageIndirect");
}

void SM_AdrMode_StackpointerInterrupt(SMCpu *m_cpu){
	/* DESIGN RETHINK :-) */
}

void SM_AdrMode_StackpointerProgramcounterRelative(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerProgramcounterRelative");
}

void SM_AdrMode_StackpointerPull(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerPull");
}

void SM_AdrMode_StackpointerPush(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerPush");
}

void SM_AdrMode_StackpointerRti(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerRti");
}

void SM_AdrMode_StackpointerRtl(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerRtl");
}

void SM_AdrMode_StackpointerRts(SMCpu *m_cpu){
	/* TODO */
	NOT_IMPLEMENTED("SM_AdrMode_StackpointerRts");
}

void SM_AdrMode_StackpointerRelative(SMCpu *m_cpu){
	m_cpu->arg_effectiveAdr = toU16(m_cpu->reg_sp+SM_Cpu_fetch8(m_cpu));
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_AdrMode_StackpointerRelativeIndirectYIndexed(SMCpu *m_cpu){
	Uint16 indirect_address = m_cpu->reg_sp+SM_Cpu_fetch8(m_cpu);
	
	m_cpu->arg_effectiveAdr = toAddress(SM_Cpu_readMem16(m_cpu, indirect_address, 0x00), m_cpu->reg_dbr);
	
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->arg_effectiveAdr += m_cpu->reg_y;
	}
	/* 8-bit mode */
	else{
		m_cpu->arg_effectiveAdr += toU8(m_cpu->reg_y);
	}
	
	/* Loads data operand from memory */
	if(m_cpu->arg_mod&ADRMOD_DPLOBYTE){
		/* 16-bit mode */
		if(SMCPU_STATUS_ACU16BIT){
			m_cpu->arg_data = SM_Cpu_readMem16(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
		/* 8-bit mode */
		else{
			m_cpu->arg_data = SM_Cpu_readMem8(m_cpu, m_cpu->arg_effectiveAdr, m_cpu->reg_dbr);
		}
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}




void SM_AdrModePrint_None(SMCpu *m_cpu){
	printf("<Instruction Not Implemented>");
}

void SM_AdrModePrint_AbsoluteDBR(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("0x%x", addr);
}

void SM_AdrModePrint_AbsolutePBR(SMCpu *m_cpu){
	Uint32 addr = m_cpu->reg_pc;
	printf("0x%x", addr);
}

void SM_AdrModePrint_AbsoluteXIndexed(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("0x%x, X", addr);
}

void SM_AdrModePrint_AbsoluteYIndexed(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("0x%x, Y", addr);
}

void SM_AdrModePrint_AbsoluteIndexedIndirect(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("(0x%x, X)", addr);
}

void SM_AdrModePrint_AbsoluteIndirect(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("(0x%x)", addr);
}

void SM_AdrModePrint_AbsoluteIndirectLong(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("[0x%x]", addr);
}

void SM_AdrModePrint_AbsoluteLong(SMCpu *m_cpu){
	Uint32 addr = toAddress(SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr), SM_Cpu_readMem8(m_cpu, m_cpu->reg_pc+3, m_cpu->reg_pbr));
	printf("0x%x", addr);
}

void SM_AdrModePrint_AbsoluteLongXIndexed(SMCpu *m_cpu){
	Uint32 addr = toAddress(SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr), SM_Cpu_readMem8(m_cpu, m_cpu->reg_pc+3, m_cpu->reg_pbr));
	printf("0x%x, X", addr);
}

void SM_AdrModePrint_Acumulator(SMCpu *m_cpu){
	printf("C");
}

void SM_AdrModePrint_BlockMove(SMCpu *m_cpu){
	
}

void SM_AdrModePrint_Directpage(SMCpu *m_cpu){
	printf("dp");
}

void SM_AdrModePrint_DirectpageXIndexed(SMCpu *m_cpu){
	printf("dp, X");
}

void SM_AdrModePrint_DirectpageYIndexed(SMCpu *m_cpu){
	printf("dp, Y");
}

void SM_AdrModePrint_DirectpageXIndexedIndirect(SMCpu *m_cpu){
	printf("(dp, X)");
}

void SM_AdrModePrint_DirectpageIndirect(SMCpu *m_cpu){
	printf("(dp)");
}

void SM_AdrModePrint_DirectpageIndirectLong(SMCpu *m_cpu){
	printf("[dp]");
}

void SM_AdrModePrint_DirectpageIndirectYIndexed(SMCpu *m_cpu){
	printf("(dp), Y");
}

void SM_AdrModePrint_DirectpageIndirectLongYIndexed(SMCpu *m_cpu){
	printf("[dp], Y");
}

void SM_AdrModePrint_ImmediateAcu(SMCpu *m_cpu){
	Uint32 imm = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("$%x", imm);
}

void SM_AdrModePrint_ImmediateMem(SMCpu *m_cpu){
	Uint32 imm = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("$%x", imm);
}

void SM_AdrModePrint_ImmediateIndex(SMCpu *m_cpu){
	Uint32 imm = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("$%x", imm);
}

void SM_AdrModePrint_Implied(SMCpu *m_cpu){}

void SM_AdrModePrint_ProgramcounterRelative(SMCpu *m_cpu){
	Uint32 addr = m_cpu->reg_pc;
	printf("0x%x", addr);
}

void SM_AdrModePrint_ProgramcounterRelativeLong(SMCpu *m_cpu){
	Uint32 addr = toAddress(m_cpu->reg_pc, m_cpu->reg_pbr);
	printf("0x%x", addr);
}

void SM_AdrModePrint_StackpointerAbsolute(SMCpu *m_cpu){
	Uint32 addr = SM_Cpu_readMem16(m_cpu, m_cpu->reg_lpc+1, m_cpu->reg_pbr);
	printf("$%x", addr);
}

void SM_AdrModePrint_StackpointerDirectpageIndirect(SMCpu *m_cpu){
	printf("dp");
}

void SM_AdrModePrint_StackpointerInterrupt(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerProgramcounterRelative(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerPull(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerPush(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerRti(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerRtl(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerRts(SMCpu *m_cpu){}

void SM_AdrModePrint_StackpointerRelative(SMCpu *m_cpu){
	printf("sr, S");
}

void SM_AdrModePrint_StackpointerRelativeIndirectYIndexed(SMCpu *m_cpu){
	printf("(sr, S), Y");
}




SMAdrMode sm_adrmodes[ADRM_TOTAL] = {
	[ADRM_NONE] = {&SM_AdrMode_None, &SM_AdrModePrint_None},
	[ADRM_ABSOLUTEDBR] = {&SM_AdrMode_AbsoluteDBR, &SM_AdrModePrint_AbsoluteDBR},
	[ADRM_ABSOLUTEPBR] = {&SM_AdrMode_AbsolutePBR, &SM_AdrModePrint_AbsolutePBR},
	[ADRM_ABSOLUTE_X_INDEXED] = {&SM_AdrMode_AbsoluteXIndexed, &SM_AdrModePrint_AbsoluteXIndexed},
	[ADRM_ABSOLUTE_Y_INDEXED] = {&SM_AdrMode_AbsoluteYIndexed, &SM_AdrModePrint_AbsoluteYIndexed},
	[ADRM_ABSOLUTE_INDEXED_INDIRECT] = {&SM_AdrMode_AbsoluteIndexedIndirect, &SM_AdrModePrint_AbsoluteIndexedIndirect},
	[ADRM_ABSOLUTE_INDIRECT] = {&SM_AdrMode_AbsoluteIndirect, &SM_AdrModePrint_AbsoluteIndirect},
	[ADRM_ABSOLUTE_INDIRECT_LONG] = {&SM_AdrMode_AbsoluteIndirect, &SM_AdrModePrint_AbsoluteIndirect},
	[ADRM_ABSOLUTE_LONG] = {&SM_AdrMode_AbsoluteLong, &SM_AdrModePrint_AbsoluteLong},
	[ADRM_ABSOLUTE_LONG_X_INDEXED] = {&SM_AdrMode_AbsoluteLongXIndexed, &SM_AdrModePrint_AbsoluteLongXIndexed},
	[ADRM_ACUMULATOR] = {&SM_AdrMode_Acumulator, &SM_AdrModePrint_Acumulator},
	[ADRM_BLOCKMOVE] = {&SM_AdrMode_BlockMove, &SM_AdrModePrint_BlockMove},
	[ADRM_DIRECTPAGE] = {&SM_AdrMode_Directpage, &SM_AdrModePrint_Directpage},
	[ADRM_DIRECTPAGE_X_INDEXED] = {&SM_AdrMode_DirectpageXIndexed, &SM_AdrModePrint_DirectpageXIndexed},
	[ADRM_DIRECTPAGE_Y_INDEXED] = {&SM_AdrMode_DirectpageYIndexed, &SM_AdrModePrint_DirectpageYIndexed},
	[ADRM_DIRECTPAGE_X_INDEXED_INDIRECT] = {&SM_AdrMode_DirectpageXIndexedIndirect, &SM_AdrModePrint_DirectpageXIndexedIndirect},
	[ADRM_DIRECTPAGE_INDIRECT] = {&SM_AdrMode_DirectpageIndirect, &SM_AdrModePrint_DirectpageIndirect},
	[ADRM_DIRECTPAGE_INDIRECT_LONG] = {&SM_AdrMode_DirectpageIndirectLong, &SM_AdrModePrint_DirectpageIndirectLong},
	[ADRM_DIRECTPAGE_INDIRECT_Y_INDEXED] = {&SM_AdrMode_DirectpageIndirectYIndexed, &SM_AdrModePrint_DirectpageIndirectYIndexed},
	[ADRM_DIRECTPAGE_INDIRECT_LONG_Y_INDEXED] = {&SM_AdrMode_DirectpageIndirectLongYIndexed, &SM_AdrModePrint_DirectpageIndirectLongYIndexed},
	[ADRM_IMMEDIATEACU] = {&SM_AdrMode_ImmediateAcu, &SM_AdrModePrint_ImmediateAcu},
	[ADRM_IMMEDIATEMEM] = {&SM_AdrMode_ImmediateMem, &SM_AdrModePrint_ImmediateMem},
	[ADRM_IMMEDIATEINDEX] = {&SM_AdrMode_ImmediateIndex, &SM_AdrModePrint_ImmediateIndex},
	[ADRM_IMPLIED] = {&SM_AdrMode_Implied, &SM_AdrModePrint_Implied},
	[ADRM_PROGRAMCOUNTER_RELATIVE] = {&SM_AdrMode_ProgramcounterRelative, &SM_AdrModePrint_ProgramcounterRelative},
	[ADRM_PROGRAMCOUNTER_RELATIVE_LONG] = {&SM_AdrMode_ProgramcounterRelativeLong, &SM_AdrModePrint_ProgramcounterRelativeLong},
	[ADRM_STACKPOINTER_ABSOLUTE] = {&SM_AdrMode_StackpointerAbsolute, &SM_AdrModePrint_StackpointerAbsolute},
	[ADRM_STACKPOINTER_DIRECTPAGE_INDIRECT] = {&SM_AdrMode_StackpointerDirectpageIndirect, &SM_AdrModePrint_StackpointerDirectpageIndirect},
	[ADRM_STACKPOINTER_INTERRUPT] = {&SM_AdrMode_StackpointerInterrupt, &SM_AdrModePrint_StackpointerInterrupt},
	[ADRM_STACKPOINTER_PROGRAMCOUNTER_RELATIVE] = {&SM_AdrMode_StackpointerProgramcounterRelative, &SM_AdrModePrint_StackpointerProgramcounterRelative},
	[ADRM_STACKPOINTER_PULL] = {&SM_AdrMode_StackpointerPull, &SM_AdrModePrint_StackpointerPull},
	[ADRM_STACKPOINTER_PUSH] = {&SM_AdrMode_StackpointerPush, &SM_AdrModePrint_StackpointerPush},
	[ADRM_STACKPOINTER_RTI] = {&SM_AdrMode_StackpointerRti, &SM_AdrModePrint_StackpointerRti},
	[ADRM_STACKPOINTER_RTL] = {&SM_AdrMode_StackpointerRtl, &SM_AdrModePrint_StackpointerRtl},
	[ADRM_STACKPOINTER_RTS] = {&SM_AdrMode_StackpointerRts, &SM_AdrModePrint_StackpointerRts},
	[ADRM_STACKPOINTER_RELATIVE] = {&SM_AdrMode_StackpointerRelative, &SM_AdrModePrint_StackpointerRelative},
	[ADRM_STACKPOINTER_RELATIVE_INDIRECT_Y_INDEXED] = {&SM_AdrMode_StackpointerRelativeIndirectYIndexed, &SM_AdrModePrint_StackpointerRelativeIndirectYIndexed},
};

