#include "cpu.h"


const SMIntType SM_INT_IRQ	 = {0xFFFE, 0xFFEE};
const SMIntType SM_INT_RESET = {0xFFFC, 0x0000};
const SMIntType SM_INT_NMI	 = {0xFFFA, 0xFFEA};
const SMIntType SM_INT_ABORT = {0xFFF8, 0xFFE8};
const SMIntType SM_INT_BRK	 = {0xFFFE, 0xFFE6};
const SMIntType SM_INT_COP	 = {0xFFF4, 0xFFE4};


Uint8 SM_Cpu_readMem8(SMCpu *m_cpu, Uint16 offset, Uint8 bank){
	Uint8 data = 0;
	SM_Cpu_readBus(m_cpu, toAddress(offset, bank), data);
	return data;
}

Uint16 SM_Cpu_readMem16(SMCpu *m_cpu, Uint16 offset, Uint8 bank){
	Uint8 lo = 0, hi = 0;
	Uint16 data;
	SM_Cpu_readBus(m_cpu, toAddress(offset, bank), lo);
	offset++;
	SM_Cpu_readBus(m_cpu, toAddress(offset, bank), hi);
	data = toWord(lo, hi);
	return data;
}


void SM_Cpu_writeMem8(SMCpu *m_cpu, Uint16 offset, Uint8 bank, Uint8 data){
	SM_Cpu_writeBus(m_cpu, toAddress(offset, bank), data);
}

void SM_Cpu_writeMem16(SMCpu *m_cpu, Uint16 offset, Uint8 bank, Uint16 data){
	SM_Cpu_writeBus(m_cpu, toAddress(offset, bank), lowByte(data));
	offset++;
	SM_Cpu_writeBus(m_cpu, toAddress(offset, bank), highByte(data));
}


Uint8 SM_Cpu_pop8(SMCpu *m_cpu){
	Uint8 data = 0;
	m_cpu->reg_sp++;
	SM_Cpu_readBus(m_cpu, m_cpu->reg_sp, data);
	return data;
}

Uint16 SM_Cpu_pop16(SMCpu *m_cpu){
	Uint8 lo = 0, hi = 0;
	Uint16 data;
	m_cpu->reg_sp++;
	SM_Cpu_readBus(m_cpu, m_cpu->reg_sp, lo);
	m_cpu->reg_sp++;
	SM_Cpu_readBus(m_cpu, m_cpu->reg_sp, hi);
	data = toWord(lo, hi);
	return data;
}


void SM_Cpu_push8(SMCpu *m_cpu, Uint8 data){
	SM_Cpu_writeBus(m_cpu, m_cpu->reg_sp, data);
	m_cpu->reg_sp--;
}

void SM_Cpu_push16(SMCpu *m_cpu, Uint16 data){
	SM_Cpu_writeBus(m_cpu, m_cpu->reg_sp, highByte(data));
	m_cpu->reg_sp--;
	SM_Cpu_writeBus(m_cpu, m_cpu->reg_sp, lowByte(data));
	m_cpu->reg_sp--;
}


Uint8 SM_Cpu_fetch8(SMCpu *m_cpu){
	Uint8 data = 0;
	SM_Cpu_readBus(m_cpu, toAddress(m_cpu->reg_pc, m_cpu->reg_pbr), data);
	m_cpu->reg_pc++;
	return data;
}

Uint16 SM_Cpu_fetch16(SMCpu *m_cpu){
	Uint8 lo = 0, hi = 0;
	Uint16 data;
	SM_Cpu_readBus(m_cpu, toAddress(m_cpu->reg_pc, m_cpu->reg_pbr), lo);
	m_cpu->reg_pc++;
	SM_Cpu_readBus(m_cpu, toAddress(m_cpu->reg_pc, m_cpu->reg_pbr), hi);
	m_cpu->reg_pc++;
	data = toWord(lo, hi);
	return data;
}


/**
	CPU INTERRUPTIONS
*/

void SM_Cpu_intCall(SMCpu *m_cpu, SMIntType interrupt){
	SM_Cpu_fetch8(m_cpu); /* Advances one byte more in program */
	if(SMCPU_STATUS_NATIVE16BIT){
		SM_Cpu_push8(m_cpu, m_cpu->reg_pbr);
		SM_Cpu_push16(m_cpu, m_cpu->reg_pc);
		SM_Cpu_push8(m_cpu, m_cpu->reg_psr);
		m_cpu->reg_pbr = 0x00;
		m_cpu->reg_pc = SM_Cpu_readMem16(m_cpu, interrupt.native, 0x00);
		SM_Emu_emuCycles(m_cpu, 1);
	}
	else{
		SM_Cpu_push16(m_cpu, m_cpu->reg_pc);
		m_cpu->reg_psr = setBit(m_cpu->reg_psr, SM_FLAG_B);
		SM_Cpu_push8(m_cpu, m_cpu->reg_psr);
		m_cpu->reg_pbr = 0x00;
		m_cpu->reg_pc = SM_Cpu_readMem16(m_cpu, interrupt.emulation, 0x00);
	}
	m_cpu->reg_psr = clrBit(m_cpu->reg_psr, SM_FLAG_D);
	m_cpu->reg_psr = setBit(m_cpu->reg_psr, SM_FLAG_I);
}

void SM_Cpu_intReturn(SMCpu *m_cpu){
	if(SMCPU_STATUS_NATIVE16BIT){
		m_cpu->reg_psr = SM_Cpu_pop8(m_cpu);
		m_cpu->reg_pc = SM_Cpu_pop16(m_cpu);
		m_cpu->reg_pbr = SM_Cpu_pop8(m_cpu);
		SM_Emu_emuCycles(m_cpu, 1);
	}
	else{
		m_cpu->reg_pc = SM_Cpu_pop16(m_cpu);
		m_cpu->reg_pbr = SM_Cpu_pop8(m_cpu);
	}
}


/**
	CPU FUNCTIONS
*/

void SM_Cpu_restart(SMCpu *m_cpu){
	/* Reset Registers */
	m_cpu->reg_acu = m_cpu->reg_dbr = 
		m_cpu->reg_x = m_cpu->reg_y = 
		m_cpu->reg_dp = m_cpu->reg_sp = 0;
	/* Reset Flags */
	m_cpu->reg_dbr = m_cpu->reg_psr = 0;
	m_cpu->flag_e = 1;
	/* Reset Instruction and Fetched Data */
	m_cpu->instruction = NULL;
	m_cpu->arg_fetchedI =
		m_cpu->arg_data = m_cpu->arg_effectiveAdr = 0;
	
	/* Reset Program Counter and Program Bank */
	m_cpu->reg_pbr = 0;
	m_cpu->reg_pc = SM_Cpu_readMem16(m_cpu, SM_INT_RESET.emulation, 0x00);
	m_cpu->reg_lpc = m_cpu->reg_pc;
	
	/* Reset Control and Properties */
	m_cpu->waiting = FALSE;
	m_cpu->cycles_count = 0;
	
	/**
		AUTO INITIALIZED CPU
	*/
	
	m_cpu->reg_acu = SM_INT_RESET.emulation;
	m_cpu->reg_x = 0x0004;
	m_cpu->reg_y = 0x0000;
	m_cpu->reg_dp = 0x0000;
	m_cpu->reg_sp = 0x01FF;
	m_cpu->reg_dbr = 0x00;
	m_cpu->reg_psr = 0x34;
}

void SM_Cpu_step(SMCpu *m_cpu){
	if(m_cpu->waiting){
		SM_Emu_emuCycles(m_cpu, 1);
		return;
	}
	
	Uint32 last_address = toAddress(m_cpu->reg_pc, m_cpu->reg_pbr);
	/*if(last_address==0){
		SM_Cpu_dumpBus(m_cpu, "dump1.bin");
		exit(0);
	}*/
	
	/* Fetch Next Instruction */
	m_cpu->arg_fetchedI = SM_Cpu_fetch8(m_cpu);
	
	/* Decode Instruction */
	m_cpu->instruction = &sm_instructions[m_cpu->arg_fetchedI];
	
	printf("0x%.6X: [0x%.2x] %s ", last_address, m_cpu->arg_fetchedI, m_cpu->instruction->mnemonic); /* Execution Log */
	
	/* Process Addressing Mode */
	m_cpu->arg_mod = m_cpu->instruction->adrmmodifier;
	sm_adrmodes[m_cpu->instruction->adrmode].adrmfunc(m_cpu);
	
	/* Execute Instruction */
	m_cpu->instruction->procedure(m_cpu);
	SM_Emu_emuCycles(m_cpu, m_cpu->instruction->cycles);
	
	sm_adrmodes[m_cpu->instruction->adrmode].adrmpfunc(m_cpu);
	m_cpu->reg_lpc = toAddress(m_cpu->reg_pc, m_cpu->reg_pbr);
	
	printf("; (0x%.2x, 0x%.2x, 0x%.2x): TIME %d; psr: 0x%x",
			SM_Cpu_readMem8(m_cpu, last_address+1, m_cpu->reg_pbr),
			SM_Cpu_readMem8(m_cpu, last_address+2, m_cpu->reg_pbr),
			SM_Cpu_readMem8(m_cpu, last_address+3, m_cpu->reg_pbr), 
			m_cpu->cycles_count, m_cpu->reg_psr); /* Execution Log */
	printf("\n\t\t\tA: 0x%.4x  X: 0x%.4x  Y: 0x%.4x  DP: 0x%.4x  SP: 0x%.4x  DBR: 0x%.2x",
			m_cpu->reg_acu, m_cpu->reg_x, m_cpu->reg_y, m_cpu->reg_dp, m_cpu->reg_sp, m_cpu->reg_dbr);
	printf("\n\t\t\tC: %x   Z: %x   I: %x   D: %x   X: %x   M: %x   V: %x   N: %x   E: %x\n\n\n",
			getBit(m_cpu->reg_psr, SM_FLAG_C), getBit(m_cpu->reg_psr, SM_FLAG_Z),
			getBit(m_cpu->reg_psr, SM_FLAG_I), getBit(m_cpu->reg_psr, SM_FLAG_D),
			getBit(m_cpu->reg_psr, SM_FLAG_X), getBit(m_cpu->reg_psr, SM_FLAG_M),
			getBit(m_cpu->reg_psr, SM_FLAG_V), getBit(m_cpu->reg_psr, SM_FLAG_N),
			m_cpu->flag_e);
	
}

