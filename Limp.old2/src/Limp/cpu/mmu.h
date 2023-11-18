#ifndef limp_cpu_mmu_h
#define limp_cpu_mmu_h

#include "cpu.h"


/**
	DIRECT BUS ACCESS FROM CPU FUNCTIONS
*/

#define LIMP_CPU_get_bus8(m_cpu, addr) LUint8(m_cpu->pins.device_bus->get8(addr))
#define LIMP_CPU_get_bus16(m_cpu, addr) LUint16(m_cpu->pins.device_bus->get16(addr))
#define LIMP_CPU_get_bus32(m_cpu, addr) LUint32(m_cpu->pins.device_bus->get32(addr))
#define LIMP_CPU_set_bus8(m_cpu, addr, data) (m_cpu->pins.device_bus->set8(addr, data))
#define LIMP_CPU_set_bus16(m_cpu, addr, data) (m_cpu->pins.device_bus->set16(addr, data))
#define LIMP_CPU_set_bus32(m_cpu, addr, data) (m_cpu->pins.device_bus->set32(addr, data))


/**
	MEMORY ACCESS FUNCTIONS
*/

#define LIMP_CPU_getMem8(m_cpu, addr, in){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_read);\
		in = LIMP_CPU_get_bus8(m_cpu, l_addr);\
	}
#define LIMP_CPU_getMem16(m_cpu, addr, in){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_read);\
		in = LIMP_CPU_get_bus16(m_cpu, l_addr);\
	}
#define LIMP_CPU_getMem32(m_cpu, addr, in){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_read);\
		in = LIMP_CPU_get_bus32(m_cpu, l_addr);\
	}
#define LIMP_CPU_setMem8(m_cpu, addr, data){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_write);\
		LIMP_CPU_set_bus8(m_cpu, l_addr, data);\
	}
#define LIMP_CPU_setMem16(m_cpu, addr, data){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_write);\
		LIMP_CPU_set_bus16(m_cpu, l_addr, data);\
	}
#define LIMP_CPU_setMem32(m_cpu, addr, data){\
		Luint32 l_addr = LIMP_MMU_translate(m_cpu, addr, LIMMUDA_data|LIMMUDA_write);\
		LIMP_CPU_set_bus32(m_cpu, l_addr, data);\
	}


/**
	STACK ACCESS FUNCTIONS
*/

#define LIMP_CPU_pop(m_cpu, in){\
		Luint32 l_sp = LIMP_CPU_getReg_ESP(m_cpu);\
		Luint32 l_addr = LIMP_MMU_translate(l_sp, LIMMUDA_data|LIMMUDA_read);\
		in = LIMP_CPU_get_bus32(m_cpu, l_addr);\
		l_sp += 4;\
		LIMP_CPU_setReg_ESP(m_cpu, l_sp);\
	}
#define LIMP_CPU_push(m_cpu, data){\
		Luint32 l_sp = LIMP_CPU_getReg_ESP(m_cpu);\
		l_sp -= 4;\
		Luint32 l_addr = LIMP_MMU_translate(l_sp, LIMMUDA_data|LIMMUDA_write);\
		LIMP_CPU_set_bus32(m_cpu, l_addr, data);\
		LIMP_CPU_setReg_ESP(m_cpu, l_sp);\
	}


/**
	MEMORY ACCESS TRANSLATION
*/

typedef enum LIMMUDA{
	LIMMUDA_code = 0x1,
	LIMMUDA_data = 0x2,
	
	LIMMUDA_write = 0x10,
	LIMMUDA_read = 0x20,
	LIMMUDA_execute = 0x40,
}LIMMUDA;

/* Memory Data Access */
Luint32 LIMP_MMU_taData(LIMPCpu *m_cpu, Luint32 address, LIMMUDA access);

/* Instruction Access */
Luint32 LIMP_MMU_taInstruction(LIMPCpu *m_cpu, Luint32 address, LIMMUDA access);


/**
	INSTRUCTION FETCHING FROM CPU MEMORY
*/

Luint32 LIMP_CPU_fetch(LIMPCpu *m_cpu);


#endif
