#ifndef snemus_cpu_procedure_h
#define snemus_cpu_procedure_h

#include "cpu.h"

void SM_Proc_notimplemented(SMCpu *m_cpu);

void SM_Proc_nop(SMCpu *m_cpu);

void SM_Proc_wdm(SMCpu *m_cpu);

void SM_Proc_inca(SMCpu *m_cpu);
void SM_Proc_inc(SMCpu *m_cpu);
void SM_Proc_inx(SMCpu *m_cpu);
void SM_Proc_iny(SMCpu *m_cpu);
void SM_Proc_deca(SMCpu *m_cpu);
void SM_Proc_dec(SMCpu *m_cpu);
void SM_Proc_dex(SMCpu *m_cpu);
void SM_Proc_dey(SMCpu *m_cpu);
void SM_Proc_adc(SMCpu *m_cpu);
void SM_Proc_sbc(SMCpu *m_cpu);
void SM_Proc_cmp(SMCpu *m_cpu);
void SM_Proc_cpx(SMCpu *m_cpu);
void SM_Proc_cpy(SMCpu *m_cpu);
void SM_Proc_biti(SMCpu *m_cpu);
void SM_Proc_bit(SMCpu *m_cpu);
void SM_Proc_and(SMCpu *m_cpu);
void SM_Proc_eor(SMCpu *m_cpu);
void SM_Proc_ora(SMCpu *m_cpu);
void SM_Proc_asla(SMCpu *m_cpu);
void SM_Proc_asl(SMCpu *m_cpu);
void SM_Proc_lsra(SMCpu *m_cpu);
void SM_Proc_lsr(SMCpu *m_cpu);
void SM_Proc_rola(SMCpu *m_cpu);
void SM_Proc_rol(SMCpu *m_cpu);
void SM_Proc_rora(SMCpu *m_cpu);
void SM_Proc_ror(SMCpu *m_cpu);

void SM_Proc_trb(SMCpu *m_cpu);
void SM_Proc_tsb(SMCpu *m_cpu);

void SM_Proc_bcc(SMCpu *m_cpu);
void SM_Proc_bcs(SMCpu *m_cpu);
void SM_Proc_beq(SMCpu *m_cpu);
void SM_Proc_bmi(SMCpu *m_cpu);
void SM_Proc_bne(SMCpu *m_cpu);
void SM_Proc_bpl(SMCpu *m_cpu);
void SM_Proc_bra(SMCpu *m_cpu);
void SM_Proc_brl(SMCpu *m_cpu);
void SM_Proc_bvc(SMCpu *m_cpu);
void SM_Proc_bvs(SMCpu *m_cpu);
void SM_Proc_jmp(SMCpu *m_cpu);
void SM_Proc_jsl(SMCpu *m_cpu);
void SM_Proc_jsr(SMCpu *m_cpu);
void SM_Proc_rtl(SMCpu *m_cpu);
void SM_Proc_rts(SMCpu *m_cpu);

void SM_Proc_brk(SMCpu *m_cpu);
void SM_Proc_cop(SMCpu *m_cpu);
void SM_Proc_rti(SMCpu *m_cpu);
void SM_Proc_stp(SMCpu *m_cpu);
void SM_Proc_wai(SMCpu *m_cpu);

void SM_Proc_lda(SMCpu *m_cpu);
void SM_Proc_ldx(SMCpu *m_cpu);
void SM_Proc_ldy(SMCpu *m_cpu);
void SM_Proc_sta(SMCpu *m_cpu);
void SM_Proc_stx(SMCpu *m_cpu);
void SM_Proc_sty(SMCpu *m_cpu);
void SM_Proc_stz(SMCpu *m_cpu);

void SM_Proc_tax(SMCpu *m_cpu);
void SM_Proc_tay(SMCpu *m_cpu);
void SM_Proc_tcd(SMCpu *m_cpu);
void SM_Proc_tcs(SMCpu *m_cpu);
void SM_Proc_tdc(SMCpu *m_cpu);
void SM_Proc_tsc(SMCpu *m_cpu);
void SM_Proc_tsx(SMCpu *m_cpu);
void SM_Proc_txa(SMCpu *m_cpu);
void SM_Proc_txs(SMCpu *m_cpu);
void SM_Proc_txy(SMCpu *m_cpu);
void SM_Proc_tya(SMCpu *m_cpu);
void SM_Proc_tyx(SMCpu *m_cpu);
void SM_Proc_xba(SMCpu *m_cpu);
void SM_Proc_mvn(SMCpu *m_cpu);
void SM_Proc_mvp(SMCpu *m_cpu);

void SM_Proc_pea(SMCpu *m_cpu);
void SM_Proc_pei(SMCpu *m_cpu);
void SM_Proc_per(SMCpu *m_cpu);
void SM_Proc_pha(SMCpu *m_cpu);
void SM_Proc_phb(SMCpu *m_cpu);
void SM_Proc_phd(SMCpu *m_cpu);
void SM_Proc_phk(SMCpu *m_cpu);
void SM_Proc_php(SMCpu *m_cpu);
void SM_Proc_phx(SMCpu *m_cpu);
void SM_Proc_phy(SMCpu *m_cpu);
void SM_Proc_pla(SMCpu *m_cpu);
void SM_Proc_plb(SMCpu *m_cpu);
void SM_Proc_pld(SMCpu *m_cpu);
void SM_Proc_plp(SMCpu *m_cpu);
void SM_Proc_plx(SMCpu *m_cpu);
void SM_Proc_ply(SMCpu *m_cpu);

void SM_Proc_clc(SMCpu *m_cpu);
void SM_Proc_cld(SMCpu *m_cpu);
void SM_Proc_cli(SMCpu *m_cpu);
void SM_Proc_clv(SMCpu *m_cpu);
void SM_Proc_sec(SMCpu *m_cpu);
void SM_Proc_sed(SMCpu *m_cpu);
void SM_Proc_sei(SMCpu *m_cpu);
void SM_Proc_rep(SMCpu *m_cpu);
void SM_Proc_sep(SMCpu *m_cpu);
void SM_Proc_xce(SMCpu *m_cpu);


#endif // snemus_cpu_procedure_h
