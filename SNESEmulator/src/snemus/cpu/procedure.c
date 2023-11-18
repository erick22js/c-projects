#include "cpu.h"
#include "../emulation.h"


void SM_Proc_notimplemented(SMCpu *m_cpu){
	NOT_IMPLEMENTED("OPCODE");
}


void SM_Proc_nop(SMCpu *m_cpu){
	/* No Operation */
}


void SM_Proc_wdm(SMCpu *m_cpu){
	/* Reserved for Expansion (unused) */
	SM_Cpu_fetch8(m_cpu);
	/* This instruction is 2 bytes long at least */
}


void SM_Proc_inca(SMCpu *m_cpu){
	if(SMCPU_STATUS_MEMORY16BIT){
		m_cpu->reg_acu++;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_acu);
	}
	else{
		m_cpu->reg_acu = toU8(m_cpu->reg_acu+1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_acu);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_inc(SMCpu *m_cpu){
	m_cpu->arg_data++;
	
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), m_cpu->arg_data);
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
		SM_Emu_emuCycles(m_cpu, 1);
	}
	else{
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
	}
}

void SM_Proc_inx(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_x++;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_x);
	}
	else{
		m_cpu->reg_x = toU8(m_cpu->reg_x+1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_x);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_iny(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_y++;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
	}
	else{
		m_cpu->reg_y = toU8(m_cpu->reg_x+1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_y);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_deca(SMCpu *m_cpu){
	if(SMCPU_STATUS_MEMORY16BIT){
		m_cpu->reg_acu--;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_acu);
	}
	else{
		m_cpu->reg_acu = toU8(m_cpu->reg_acu-1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_acu);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_dec(SMCpu *m_cpu){
	m_cpu->arg_data--;
	
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), m_cpu->arg_data);
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
		SM_Emu_emuCycles(m_cpu, 1);
	}
	else{
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
	}
}

void SM_Proc_dex(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_x--;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_x);
	}
	else{
		m_cpu->reg_x = toU8(m_cpu->reg_x-1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_x);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_dey(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_y--;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
	}
	else{
		m_cpu->reg_y = toU8(m_cpu->reg_x-1);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_y);
		/*
			OBS: The MSB may be changed or not, but is not specified
		*/
	}
}

void SM_Proc_adc(SMCpu *m_cpu){
	Uint32 data_add;
	
	if(SMCPU_STATUS_MEMORY16BIT){
		data_add = m_cpu->reg_acu+getBit(m_cpu->reg_psr, SM_FLAG_C);
		data_add += m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
		SM_Cpu_setFlag_V(m_cpu, (toS16(toU16(data_add))<toS16(m_cpu->reg_acu)));
		SM_Cpu_setFlag_C(m_cpu, data_add>>16);
	}
	else{
		data_add = toU8(m_cpu->reg_acu)+getBit(m_cpu->reg_psr, SM_FLAG_C);
		data_add += toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_y);
		SM_Cpu_setFlag_V(m_cpu, (toS8(toU8(data_add))<toS8(m_cpu->reg_acu)));
		SM_Cpu_setFlag_C(m_cpu, data_add>>8);
	}
	
	/* Decimal Adjust */
	if(getBit(m_cpu->reg_psr, SM_FLAG_D)){
		if((data_add&0x000F)>0x0009){
			data_add += 0x0006;
		}
		if((data_add&0x00F0)>0x0090){
			data_add += 0x0060;
		}
		if((data_add&0x0F00)>0x0900){
			data_add += 0x0600;
		}
		if((data_add&0xF000)>0x9000){
			data_add += 0x6000;
		}
	}
	
	m_cpu->reg_acu = data_add;
	/*
		WARNING: To revise if the way the overflow flag is set its right, and the bcd encoding (anyway snes does not
		support it).
	*/
}

void SM_Proc_sbc(SMCpu *m_cpu){
	Uint32 data_sub;
	
	if(SMCPU_STATUS_MEMORY16BIT){
		data_sub = m_cpu->reg_acu+getBit(m_cpu->reg_psr, SM_FLAG_C)-1;
		data_sub -= m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
		SM_Cpu_setFlag_V(m_cpu, (toS16(toU16(data_sub))>toS16(m_cpu->reg_acu)));
		SM_Cpu_setFlag_C(m_cpu, !(data_sub>>16));
	}
	else{
		data_sub = toU8(m_cpu->reg_acu)+getBit(m_cpu->reg_psr, SM_FLAG_C)-1;
		data_sub -= toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->reg_y);
		SM_Cpu_setFlag_V(m_cpu, (toS8(toU8(data_sub))>toS8(m_cpu->reg_acu)));
		SM_Cpu_setFlag_C(m_cpu, !(data_sub>>16));
	}
	
	/* Decimal Adjust */
	if(getBit(m_cpu->reg_psr, SM_FLAG_D)){
		if((data_sub&0x000F)>0x0009){
			data_sub += 0x0006;
		}
		if((data_sub&0x00F0)>0x0090){
			data_sub += 0x0060;
		}
		if((data_sub&0x0F00)>0x0900){
			data_sub += 0x0600;
		}
		if((data_sub&0xF000)>0x9000){
			data_sub += 0x6000;
		}
	}
	
	m_cpu->reg_acu = data_sub;
	/*
		WARNING: To revise if the way the overflow flag is set its right, and the bcd encoding (anyway snes does not
		support it).
	*/
}

void SM_Proc_cmp(SMCpu *m_cpu){
	if(SMCPU_STATUS_MEMORY16BIT){
		Uint32 data_cmp = m_cpu->reg_acu-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, toU16(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>16));
	}
	else{
		Uint32 data_cmp = toU8(m_cpu->reg_acu)-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>8));
	}
}

void SM_Proc_cpx(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		Uint32 data_cmp = m_cpu->reg_x-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, toU16(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>16));
	}
	else{
		Uint32 data_cmp = toU8(m_cpu->reg_x)-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>8));
	}
}

void SM_Proc_cpy(SMCpu *m_cpu){
	if(SMCPU_STATUS_INDEX16BIT){
		Uint32 data_cmp = m_cpu->reg_y-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, toU16(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>16));
	}
	else{
		Uint32 data_cmp = toU8(m_cpu->reg_y)-m_cpu->arg_data;
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(data_cmp));
		SM_Cpu_setFlag_C(m_cpu, !(data_cmp>>8));
	}
}

void SM_Proc_biti(SMCpu *m_cpu){
	if(SMCPU_STATUS_MEMORY16BIT){
		Uint16 test_data = m_cpu->arg_data&m_cpu->reg_acu;
		SM_Cpu_setFlag_Z(m_cpu, test_data);
	}
	else{
		Uint8 test_data = m_cpu->arg_data&m_cpu->reg_acu;
		SM_Cpu_setFlag_Z(m_cpu, test_data);
	}
}

void SM_Proc_bit(SMCpu *m_cpu){
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_V16(m_cpu, m_cpu->arg_data);
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
		Uint16 test_data = m_cpu->arg_data&m_cpu->reg_acu;
		SM_Cpu_setFlag_Z(m_cpu, test_data);
	}
	else{
		SM_Cpu_setFlag_V8(m_cpu, m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
		Uint8 test_data = m_cpu->arg_data&m_cpu->reg_acu;
		SM_Cpu_setFlag_Z(m_cpu, test_data);
	}
}

void SM_Proc_and(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->reg_acu &= m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_acu &= toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->arg_data));
	}
}

void SM_Proc_eor(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->reg_acu ^= m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_acu ^= toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->arg_data));
	}
}

void SM_Proc_ora(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->reg_acu |= m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_acu |= toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->arg_data));
	}
}

void SM_Proc_asla(SMCpu *m_cpu){
	Uint16 operand = m_cpu->reg_acu;
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand <<= 1;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		m_cpu->reg_acu = operand;
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand <<= 1;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		m_cpu->reg_acu = toU8(operand);
	}
}

void SM_Proc_asl(SMCpu *m_cpu){
	Uint16 operand = m_cpu->arg_data;
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand <<= 1;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand <<= 1;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_Proc_lsra(SMCpu *m_cpu){
	Uint16 operand = m_cpu->reg_acu;
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x1);
		operand >>= 1;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		m_cpu->reg_acu = operand;
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x1);
		operand >>= 1;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		m_cpu->reg_acu = toU8(operand);
	}
}

void SM_Proc_lsr(SMCpu *m_cpu){
	Uint16 operand = m_cpu->arg_data;
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x1);
		operand >>= 1;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x1);
		operand >>= 1;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_Proc_rola(SMCpu *m_cpu){
	Uint16 operand = m_cpu->reg_acu;
	Bool flag_c = getBit(m_cpu->reg_psr, SM_FLAG_C);
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand <<= 1;
		operand |= flag_c;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		m_cpu->reg_acu = operand;
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand <<= 1;
		operand |= flag_c;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		m_cpu->reg_acu = toU8(operand);
	}
}

void SM_Proc_rol(SMCpu *m_cpu){
	Uint16 operand = m_cpu->arg_data;
	Bool flag_c = getBit(m_cpu->reg_psr, SM_FLAG_C);
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand <<= 1;
		operand |= flag_c;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand <<= 1;
		operand |= flag_c;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_Proc_rora(SMCpu *m_cpu){
	Uint16 operand = m_cpu->reg_acu;
	Bool flag_c = getBit(m_cpu->reg_psr, SM_FLAG_C);
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand >>= 1;
		operand |= flag_c<<7;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		m_cpu->reg_acu = operand;
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand >>= 1;
		operand |= flag_c<<15;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		m_cpu->reg_acu = toU8(operand);
	}
}

void SM_Proc_ror(SMCpu *m_cpu){
	Uint16 operand = m_cpu->arg_data;
	Bool flag_c = getBit(m_cpu->reg_psr, SM_FLAG_C);
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_setFlag_C(m_cpu, operand&0x8000);
		operand >>= 1;
		operand |= flag_c<<15;
		SM_Cpu_setFlag_NZ16(m_cpu, operand);
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_setFlag_C(m_cpu, operand&0x80);
		operand >>= 1;
		operand |= flag_c<<7;
		SM_Cpu_setFlag_NZ8(m_cpu, operand);
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), operand);
	}
	
	/* Memory Access of 16-bit, increases 1 cycle in general instructions */
	if(!getBit(m_cpu->reg_psr, SM_FLAG_M)){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}


void SM_Proc_trb(SMCpu *m_cpu){
	Uint16 result = m_cpu->reg_acu&m_cpu->arg_data;
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), result);
		SM_Cpu_setFlag_Z(m_cpu, result);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), result);
		SM_Cpu_setFlag_Z(m_cpu, toU8(result));
	}
}

void SM_Proc_tsb(SMCpu *m_cpu){
	Uint16 result = m_cpu->reg_acu|m_cpu->arg_data;
	/* 16-bit mode */
	if(SMCPU_STATUS_MEMORY16BIT){
		SM_Cpu_writeMem16(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), result);
		SM_Cpu_setFlag_Z(m_cpu, result);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, m_cpu->arg_effectiveAdr, aBank(m_cpu->arg_effectiveAdr), result);
		SM_Cpu_setFlag_Z(m_cpu, toU8(result));
	}
}


void SM_Proc_bcc(SMCpu *m_cpu){
	if(!getBit(m_cpu->reg_psr, SM_FLAG_C)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bcs(SMCpu *m_cpu){
	if(getBit(m_cpu->reg_psr, SM_FLAG_C)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_beq(SMCpu *m_cpu){
	if(getBit(m_cpu->reg_psr, SM_FLAG_Z)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bmi(SMCpu *m_cpu){
	if(getBit(m_cpu->reg_psr, SM_FLAG_N)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bne(SMCpu *m_cpu){
	if(!getBit(m_cpu->reg_psr, SM_FLAG_Z)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bpl(SMCpu *m_cpu){
	if(!getBit(m_cpu->reg_psr, SM_FLAG_N)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bra(SMCpu *m_cpu){
	m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
	SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
}

void SM_Proc_brl(SMCpu *m_cpu){
	m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
}

void SM_Proc_bvc(SMCpu *m_cpu){
	if(!getBit(m_cpu->reg_psr, SM_FLAG_V)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_bvs(SMCpu *m_cpu){
	if(getBit(m_cpu->reg_psr, SM_FLAG_V)){
		m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
		SM_Emu_emuCycles(m_cpu, m_cpu->arg_pcCrossBoundary? 2: 1);
	}
}

void SM_Proc_jmp(SMCpu *m_cpu){
	if(SMCPU_STATUS_NATIVE16BIT){
		SM_Emu_emuCycles(m_cpu, 1);
	}
	else{
		if((m_cpu->arg_effectiveAdr&0xFF)==0xFF){
			/*
				TODO: Yields a incorrect result
			*/
		}
	}
	m_cpu->reg_pc = m_cpu->arg_effectiveAdr;
	m_cpu->reg_pbr = aBank(m_cpu->arg_effectiveAdr);
	/*
		OBS: Bank may be loaded if is a long jump, but, considering all addressing modes (except for thoses long)
		loads to effective address the actual program bank, seems not needed to test this occasion
	*/
}

void SM_Proc_jsl(SMCpu *m_cpu){
	SM_Cpu_push8(m_cpu, m_cpu->reg_pbr);
	SM_Cpu_push16(m_cpu, m_cpu->reg_pc);
	m_cpu->reg_pc = m_cpu->arg_effectiveAdr-1;
	m_cpu->reg_pbr = aBank(m_cpu->arg_effectiveAdr);
}

void SM_Proc_jsr(SMCpu *m_cpu){
	if(aBank(m_cpu->arg_effectiveAdr)!=m_cpu->reg_pbr){
		SM_Cpu_push8(m_cpu, m_cpu->reg_pbr);
	}
	SM_Cpu_push16(m_cpu, m_cpu->reg_pc);
	m_cpu->reg_pc = m_cpu->arg_effectiveAdr-1;
	m_cpu->reg_pbr = aBank(m_cpu->arg_effectiveAdr);
}

void SM_Proc_rtl(SMCpu *m_cpu){
	m_cpu->reg_pbr = SM_Cpu_pop8(m_cpu);
	m_cpu->reg_pc = SM_Cpu_pop16(m_cpu)+1;
}

void SM_Proc_rts(SMCpu *m_cpu){
	m_cpu->reg_pbr = SM_Cpu_pop8(m_cpu);
	m_cpu->reg_pc = SM_Cpu_pop16(m_cpu)+1;
}


void SM_Proc_brk(SMCpu *m_cpu){
	SM_Cpu_intCall(m_cpu, SM_INT_BRK);
}

void SM_Proc_cop(SMCpu *m_cpu){
	SM_Cpu_intCall(m_cpu, SM_INT_COP);
}

void SM_Proc_rti(SMCpu *m_cpu){
	SM_Cpu_intReturn(m_cpu);
}

void SM_Proc_stp(SMCpu *m_cpu){
	/* TODO: Stop Processor */
}

void SM_Proc_wai(SMCpu *m_cpu){
	/* TODO: Wait Processor */
}


void SM_Proc_lda(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		m_cpu->reg_acu = m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_acu = toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
	}
}

void SM_Proc_ldx(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_x = m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_x = toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
	}
}

void SM_Proc_ldy(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_y = m_cpu->arg_data;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->arg_data);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_y = toU8(m_cpu->arg_data);
		SM_Cpu_setFlag_NZ8(m_cpu, m_cpu->arg_data);
	}
}

void SM_Proc_sta(SMCpu *m_cpu){
	Uint16 address = m_cpu->arg_effectiveAdr;
	Uint8 bank = aBank(m_cpu->arg_effectiveAdr);
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_writeMem16(m_cpu, address, bank, m_cpu->reg_acu);
		SM_Emu_emuCycles(m_cpu, 1); /* IF flag M==0 */
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, address, bank, m_cpu->reg_acu);
	}
}

void SM_Proc_stx(SMCpu *m_cpu){
	Uint16 address = m_cpu->arg_effectiveAdr;
	Uint8 bank = aBank(m_cpu->arg_effectiveAdr);
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		SM_Cpu_writeMem16(m_cpu, address, bank, m_cpu->reg_x);
		SM_Emu_emuCycles(m_cpu, 1); /* IF flag X==0 */
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, address, bank, m_cpu->reg_x);
	}
}

void SM_Proc_sty(SMCpu *m_cpu){
	Uint16 address = m_cpu->arg_effectiveAdr;
	Uint8 bank = aBank(m_cpu->arg_effectiveAdr);
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		SM_Cpu_writeMem16(m_cpu, address, bank, m_cpu->reg_y);
		SM_Emu_emuCycles(m_cpu, 1); /* IF flag X==0 */
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, address, bank, m_cpu->reg_y);
	}
}

void SM_Proc_stz(SMCpu *m_cpu){
	Uint16 address = m_cpu->arg_effectiveAdr;
	Uint8 bank = aBank(m_cpu->arg_effectiveAdr);
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_writeMem16(m_cpu, address, bank, 0);
		SM_Emu_emuCycles(m_cpu, 1); /* IF flag M==0 */
	}
	/* 8-bit mode */
	else{
		SM_Cpu_writeMem8(m_cpu, address, bank, 0);
	}
}


void SM_Proc_tax(SMCpu *m_cpu){
	/* Only 65816 Native Mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		/* Register X is 8-bit */
		if(getBit(m_cpu->reg_psr, SM_FLAG_X)){
			m_cpu->reg_x = toU8(m_cpu->reg_acu);
			SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_acu));
		}
		/* The operation is 16-bit */
		else{
			m_cpu->reg_x = m_cpu->reg_acu;
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_acu);
		}
	}
	/* The operation is 8-bit */
	else{
		m_cpu->reg_x = toU8(m_cpu->reg_acu);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_acu));
		/*
			OBS: Is not explict if is only the lower byte of index X in this situation is modified (keeping the
			upper byte)
		*/
	}
}

void SM_Proc_tay(SMCpu *m_cpu){
	/* Only 65816 Native Mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		/* Register X is 8-bit */
		if(getBit(m_cpu->reg_psr, SM_FLAG_X)){
			m_cpu->reg_y = toU8(m_cpu->reg_acu);
			SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_acu));
		}
		/* The operation is 16-bit */
		else{
			m_cpu->reg_y = m_cpu->reg_acu;
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_acu);
		}
	}
	/* The operation is 8-bit */
	else{
		m_cpu->reg_y = toU8(m_cpu->reg_acu);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_acu));
		/*
			OBS: Is not explict if is only the lower byte of index X in this situation is modified (keeping the
			upper byte)
		*/
	}
}

void SM_Proc_tcd(SMCpu *m_cpu){
	m_cpu->reg_dp = m_cpu->reg_acu;
	SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_acu);
}

void SM_Proc_tcs(SMCpu *m_cpu){
	m_cpu->reg_sp = m_cpu->reg_acu;
}

void SM_Proc_tdc(SMCpu *m_cpu){
	m_cpu->reg_acu = m_cpu->reg_dp;
	SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_dp);
}

void SM_Proc_tsc(SMCpu *m_cpu){
	m_cpu->reg_acu = m_cpu->reg_sp;
	SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_sp);
}

void SM_Proc_tsx(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_x = toU8(m_cpu->reg_sp);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_sp));
		/*
			OBS: Is not explict if is only the lower byte of index X in this situation is modified (keeping the
			upper byte)
		*/
	}
	else{
		m_cpu->reg_x = m_cpu->reg_sp;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_sp);
	}
}

void SM_Proc_txa(SMCpu *m_cpu){
	/* Only 65816 Native Mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		/* Register X is 8-bit */
		if(getBit(m_cpu->reg_psr, SM_FLAG_X)){
			m_cpu->reg_acu = toU8(m_cpu->reg_x);
			SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_x));
		}
		/* Acumulator is 8-bit */
		else if(getBit(m_cpu->reg_psr, SM_FLAG_M)){
			m_cpu->reg_acu = toWord(toU8(m_cpu->reg_x), highByte(m_cpu->reg_acu));
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_x);
			/*
				OBS: In docs, this occasion comes first
			*/
		}
		/* The operation is 16-bit */
		else{
			m_cpu->reg_acu = m_cpu->reg_x;
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_x);
		}
	}
	/* The operation is 8-bit */
	else{
		m_cpu->reg_acu = toU8(m_cpu->reg_x);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_x));
		/*
			OBS: Is not explict if is only the lower byte of index X in this situation is modified (keeping the
			upper byte)
		*/
	}
}

void SM_Proc_txs(SMCpu *m_cpu){
	/* Only 65816 Native Mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		/* Register X is 8-bit */
		if(getBit(m_cpu->reg_psr, SM_FLAG_X)){
			m_cpu->reg_sp = toU8(m_cpu->reg_x);
		}
		/* The operation is 16-bit */
		else{
			m_cpu->reg_sp = m_cpu->reg_x;
		}
	}
	/* The operation is 8-bit */
	else{
		m_cpu->reg_sp = toU8(m_cpu->reg_x);
	}
}

void SM_Proc_txy(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_y = m_cpu->reg_x;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_x);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_y = toU8(m_cpu->reg_x);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_x));
	}
}

void SM_Proc_tya(SMCpu *m_cpu){
	/* Only 65816 Native Mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		/* Register X is 8-bit */
		if(getBit(m_cpu->reg_psr, SM_FLAG_X)){
			m_cpu->reg_acu = toU8(m_cpu->reg_y);
			SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_y));
		}
		/* Acumulator is 8-bit */
		else if(getBit(m_cpu->reg_psr, SM_FLAG_M)){
			m_cpu->reg_acu = toWord(toU8(m_cpu->reg_y), highByte(m_cpu->reg_acu));
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
			/*
				OBS: In docs, this occasion comes first
			*/
		}
		/* The operation is 16-bit */
		else{
			m_cpu->reg_acu = m_cpu->reg_y;
			SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
		}
	}
	/* The operation is 8-bit */
	else{
		m_cpu->reg_acu = toU8(m_cpu->reg_y);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_y));
		/*
			OBS: Is not explict if is only the lower byte of index X in this situation is modified (keeping the
			upper byte)
		*/
	}
}

void SM_Proc_tyx(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_INDEX16BIT){
		m_cpu->reg_x = m_cpu->reg_y;
		SM_Cpu_setFlag_NZ16(m_cpu, m_cpu->reg_y);
	}
	/* 8-bit mode */
	else{
		m_cpu->reg_x = toU8(m_cpu->reg_y);
		SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_y));
	}
}

void SM_Proc_xba(SMCpu *m_cpu){
	m_cpu->reg_acu = toWord(highByte(m_cpu->reg_acu), lowByte(m_cpu->reg_acu));
	SM_Cpu_setFlag_NZ8(m_cpu, toU8(m_cpu->reg_acu));
}

void SM_Proc_mvn(SMCpu *m_cpu){
	Uint8 bank_dest = SM_Cpu_fetch8(m_cpu);
	Uint8 bank_src = SM_Cpu_fetch8(m_cpu);
	while(m_cpu->reg_acu!=0xFFFF){
		Uint8 byte;
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			byte = SM_Cpu_readMem8(m_cpu, m_cpu->reg_x, bank_src);
			SM_Cpu_writeMem8(m_cpu, m_cpu->reg_y, bank_dest, byte);
			m_cpu->reg_x++;
			m_cpu->reg_y++;
		}
		/* 8-bit mode */
		else{
			byte = SM_Cpu_readMem8(m_cpu, toU8(m_cpu->reg_x), bank_src);
			SM_Cpu_writeMem8(m_cpu, toU8(m_cpu->reg_y), bank_dest, byte);
			m_cpu->reg_x = toU8(m_cpu->reg_x)+1;
			m_cpu->reg_y = toU8(m_cpu->reg_y)+1;
		}
		m_cpu->reg_acu--;
		SM_Emu_emuCycles(m_cpu, 7);
	}
}

void SM_Proc_mvp(SMCpu *m_cpu){
	Uint8 bank_dest = SM_Cpu_fetch8(m_cpu);
	Uint8 bank_src = SM_Cpu_fetch8(m_cpu);
	while(m_cpu->reg_acu!=0xFFFF){
		Uint8 byte;
		/* 16-bit mode */
		if(SMCPU_STATUS_INDEX16BIT){
			byte = SM_Cpu_readMem8(m_cpu, m_cpu->reg_x, bank_src);
			SM_Cpu_writeMem8(m_cpu, m_cpu->reg_y, bank_dest, byte);
			m_cpu->reg_x--;
			m_cpu->reg_y--;
		}
		/* 8-bit mode */
		else{
			byte = SM_Cpu_readMem8(m_cpu, toU8(m_cpu->reg_x), bank_src);
			SM_Cpu_writeMem8(m_cpu, toU8(m_cpu->reg_y), bank_dest, byte);
			m_cpu->reg_x = toU8(m_cpu->reg_x)-1;
			m_cpu->reg_y = toU8(m_cpu->reg_y)-1;
		}
		m_cpu->reg_acu--;
		SM_Emu_emuCycles(m_cpu, 7);
	}
}


void SM_Proc_pea(SMCpu *m_cpu){
	Uint16 data = SM_Cpu_fetch16(m_cpu);
	SM_Cpu_push16(m_cpu, data);
}
void SM_Proc_pei(SMCpu *m_cpu){
	Uint32 address = SM_Cpu_fetch8(m_cpu)+m_cpu->reg_dp;
	Uint16 data = SM_Cpu_readMem16(m_cpu, address, 0);
	SM_Cpu_push16(m_cpu, data);
	if(m_cpu->reg_dp){
		SM_Emu_emuCycles(m_cpu, 1);
	}
}

void SM_Proc_per(SMCpu *m_cpu){
	Uint16 data = SM_Cpu_fetch16(m_cpu)+m_cpu->reg_pc;
	SM_Cpu_push16(m_cpu, data);
}

void SM_Proc_pha(SMCpu *m_cpu){
	Uint16 data = m_cpu->reg_acu;
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_push16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_push8(m_cpu, data);
	}
}

void SM_Proc_phb(SMCpu *m_cpu){
	Uint8 data = m_cpu->reg_dbr;
	SM_Cpu_push8(m_cpu, data);
}

void SM_Proc_phd(SMCpu *m_cpu){
	Uint16 data = m_cpu->reg_dp;
	SM_Cpu_push16(m_cpu, data);
}

void SM_Proc_phk(SMCpu *m_cpu){
	Uint8 data = m_cpu->reg_pbr;
	SM_Cpu_push8(m_cpu, data);
}

void SM_Proc_php(SMCpu *m_cpu){
	Uint8 data = m_cpu->reg_psr;
	SM_Cpu_push8(m_cpu, data);
}

void SM_Proc_phx(SMCpu *m_cpu){
	Uint16 data = m_cpu->reg_x;
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_push16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_push8(m_cpu, data);
	}
}

void SM_Proc_phy(SMCpu *m_cpu){
	Uint16 data = m_cpu->reg_y;
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		SM_Cpu_push16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		SM_Cpu_push8(m_cpu, data);
	}
}

void SM_Proc_pla(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		Uint16 data = SM_Cpu_pop16(m_cpu);
		m_cpu->reg_acu = data;
		SM_Cpu_setFlag_NZ16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		Uint8 data = SM_Cpu_pop8(m_cpu);
		m_cpu->reg_acu = data;
		SM_Cpu_setFlag_NZ8(m_cpu, data);
	}
}

void SM_Proc_plb(SMCpu *m_cpu){
	Uint8 data = SM_Cpu_pop8(m_cpu);
	m_cpu->reg_pbr = data;
	SM_Cpu_setFlag_NZ8(m_cpu, data);
}

void SM_Proc_pld(SMCpu *m_cpu){
	Uint16 data = SM_Cpu_pop16(m_cpu);
	m_cpu->reg_dp = data;
	SM_Cpu_setFlag_NZ16(m_cpu, data);
}

void SM_Proc_plp(SMCpu *m_cpu){
	Uint8 data = SM_Cpu_pop8(m_cpu);
	/* 16-bit mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		m_cpu->reg_psr = data;
	}
	/* 8-bit mode */
	else{
		data = clrBit(data, SM_FLAG_M);
		m_cpu->reg_psr = data;
		/*
			OBS: Is not explicit if its keep the old flag M, or is cleared when in 8-bit mode, pherhabs, does not affects
			the instruction mode (only the flag "e")
		*/
	}
}

void SM_Proc_plx(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		Uint16 data = SM_Cpu_pop16(m_cpu);
		m_cpu->reg_x = data;
		SM_Cpu_setFlag_NZ16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		Uint8 data = SM_Cpu_pop8(m_cpu);
		m_cpu->reg_x = data;
		SM_Cpu_setFlag_NZ8(m_cpu, data);
	}
}

void SM_Proc_ply(SMCpu *m_cpu){
	/* 16-bit mode */
	if(SMCPU_STATUS_ACU16BIT){
		Uint16 data = SM_Cpu_pop16(m_cpu);
		m_cpu->reg_y = data;
		SM_Cpu_setFlag_NZ16(m_cpu, data);
	}
	/* 8-bit mode */
	else{
		Uint8 data = SM_Cpu_pop8(m_cpu);
		m_cpu->reg_y = data;
		SM_Cpu_setFlag_NZ8(m_cpu, data);
	}
}


void SM_Proc_clc(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(clrBit(m_cpu->reg_psr, SM_FLAG_C));
}

void SM_Proc_cld(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(clrBit(m_cpu->reg_psr, SM_FLAG_D));
}

void SM_Proc_cli(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(clrBit(m_cpu->reg_psr, SM_FLAG_I));
}

void SM_Proc_clv(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(clrBit(m_cpu->reg_psr, SM_FLAG_V));
}

void SM_Proc_sec(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(setBit(m_cpu->reg_psr, SM_FLAG_C));
}

void SM_Proc_sed(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(setBit(m_cpu->reg_psr, SM_FLAG_D));
}

void SM_Proc_sei(SMCpu *m_cpu){
	m_cpu->reg_psr = toU8(setBit(m_cpu->reg_psr, SM_FLAG_I));
}

void SM_Proc_rep(SMCpu *m_cpu){
	Uint8 data = SM_Cpu_fetch8(m_cpu);
	
	/* 16-bit mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		m_cpu->reg_psr &= ~data;
	}
	/* 8-bit mode */
	else{
		data = clrBit(data, SM_FLAG_X);
		data = clrBit(data, SM_FLAG_M);
		m_cpu->reg_psr &= ~data;
	}
}

void SM_Proc_sep(SMCpu *m_cpu){
	Uint8 data = SM_Cpu_fetch8(m_cpu);
	
	/* 16-bit mode */
	if(SMCPU_STATUS_NATIVE16BIT){
		m_cpu->reg_psr |= data;
	}
	/* 8-bit mode */
	else{
		data = clrBit(data, SM_FLAG_X);
		data = clrBit(data, SM_FLAG_M);
		m_cpu->reg_psr |= data;
	}
}

void SM_Proc_xce(SMCpu *m_cpu){
	Bool flag_c = getBit(m_cpu->reg_psr, SM_FLAG_C);
	m_cpu->reg_psr = putBit(m_cpu->reg_psr, SM_FLAG_C, m_cpu->flag_e);
	m_cpu->flag_e = flag_c;
}
