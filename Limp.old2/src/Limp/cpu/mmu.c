#include "mmu.h"


/**
	MEMORY ACCESS TRANSLATION
*/

/* Translate Data Access */
Luint32 LIMP_MMU_translate(LIMPCpu *m_cpu, Luint32 address, LIMMUDA access){
	
	if(m_cpu->reg_st.pg){
		/* Table Descriptor */
		Luint32 sel_table = (address>>22);
		Luint32 desc_table = LIMP_CPU_get_bus32(m_cpu, m_cpu->reg_pdtr+(sel_table*4));
		if(!(desc_table&1)){
			/* TODO: Fault Table */
			
		}
		
		/* Page Descriptor */
		Luint32 addr_table = desc_table&0xfffff000;
		Luint32 sel_page = (address>>12)&0x3ff;
		Luint32 desc_page = LIMP_CPU_get_bus32(m_cpu, addr_table+(sel_page*4));
		if(!(desc_page&1)){
			/* TODO: Fault Page */
			
		}
		
		/* Page Access Testing */
		if(
			(!(desc_page&access&0x70))||
			(m_cpu->reg_st.pl>((desc_page>>2)&0x3))
			){
			/* TODO: Exception Page Access */
			
		}
		
		/* Otherwise, Translate the Logical Address to Physical */
		address = (desc_page&0xfffff000)|(address&0xfff);
	}
	
	return address;
}


/**
	INSTRUCTION FETCHING FROM CPU MEMORY
*/

Luint32 LIMP_CPU_fetch(LIMPCpu *m_cpu){
	Luint32 l_addr = LIMP_MMU_translate(m_cpu, m_cpu->reg_epc, LIMMUDA_code|LIMMUDA_read);\
	m_cpu->reg_fdt = LIMP_CPU_get_bus32(m_cpu, l_addr);
	m_cpu->reg_epc += 4;
	return m_cpu->reg_fdt;
}
