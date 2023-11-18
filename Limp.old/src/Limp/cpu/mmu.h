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
		in = LIMP_CPU_get_bus8(m_cpu, addr);\
	}
#define LIMP_CPU_getMem16(m_cpu, addr, in){\
		in = LIMP_CPU_get_bus16(m_cpu, addr);\
	}
#define LIMP_CPU_getMem32(m_cpu, addr, in){\
		in = LIMP_CPU_get_bus32(m_cpu, addr);\
	}
#define LIMP_CPU_setMem8(m_cpu, addr, data){\
		LIMP_CPU_set_bus8(m_cpu, addr, data);\
	}
#define LIMP_CPU_setMem16(m_cpu, addr, data){\
		LIMP_CPU_set_bus16(m_cpu, addr, data);\
	}
#define LIMP_CPU_setMem32(m_cpu, addr, data){\
		LIMP_CPU_set_bus32(m_cpu, addr, data);\
	}
/*
#define LIMP_CPU_getMem8(m_cpu, addr, in){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		in = LIMP_CPU_get_bus8(m_cpu, l_addr);\
	}
#define LIMP_CPU_getMem16(m_cpu, addr, in){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		in = LIMP_CPU_get_bus16(m_cpu, l_addr);\
	}
#define LIMP_CPU_getMem32(m_cpu, addr, in){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		in = LIMP_CPU_get_bus32(m_cpu, l_addr);\
	}
#define LIMP_CPU_setMem8(m_cpu, addr, data){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		LIMP_CPU_set_bus8(m_cpu, l_addr, data);\
	}
#define LIMP_CPU_setMem16(m_cpu, addr, data){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		LIMP_CPU_set_bus16(m_cpu, l_addr, data);\
	}
#define LIMP_CPU_setMem32(m_cpu, addr, data){\
		Luint32 l_addr = addr;\
		l_addr += 0;\
		LIMP_CPU_set_bus32(m_cpu, l_addr, data);\
	}
*/


/**
	INSTRUCTION FETCHING FROM CPU MEMORY
*/

Luint32 LIMP_CPU_fetch(LIMPCpu *m_cpu){
	m_cpu->reg_fdt = LIMP_CPU_get_bus32(m_cpu, m_cpu->reg_epc);
	m_cpu->reg_epc += 4;
	return m_cpu->reg_fdt;
}


#endif