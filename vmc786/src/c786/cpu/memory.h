#ifndef C786_CPU_MEMORY_H_INCLUDED
#define C786_CPU_MEMORY_H_INCLUDED

#include "cpu.h"


/*****************************************************************************
* Bus Access
* Trivial for all cpu memory accesses
*/

#define _C786Cpu_getBus8(cpu, adr, out){\
        out = (Uint8)cpu->device_bus->get8(cpu->device_bus, adr);\
    }

#define _C786Cpu_setBus8(cpu, adr, in){\
        cpu->device_bus->set8(cpu->device_bus, adr, (Uint8)in);\
    }

#define _C786Cpu_getBus16(cpu, adr, out){\
        out = (Uint16)cpu->device_bus->get16(cpu->device_bus, adr);\
    }

#define _C786Cpu_setBus16(cpu, adr, in){\
        cpu->device_bus->set16(cpu->device_bus, adr, (Uint16)in);\
    }

#define _C786Cpu_getBus32(cpu, adr, out){\
        out = (Uint32)cpu->device_bus->get32(cpu->device_bus, adr);\
    }

#define _C786Cpu_setBus32(cpu, adr, in){\
        cpu->device_bus->set32(cpu->device_bus, adr, (Uint32)in);\
    }

#include "mpage.h"
#include "msegment.h"


/*****************************************************************************
* Memory Data Access
*/

void C786Cpu_setData8(C786Cpu*, Uint32, Uint8);
Uint8 C786Cpu_getData8(C786Cpu*, Uint32);
void C786Cpu_setData16(C786Cpu*, Uint32, Uint16);
Uint16 C786Cpu_getData16(C786Cpu*, Uint32);
void C786Cpu_setData32(C786Cpu*, Uint32, Uint32);
Uint32 C786Cpu_getData32(C786Cpu*, Uint32);

void C786Cpu_pushData8(C786Cpu*, Uint8);
Uint8 C786Cpu_popData8(C786Cpu*);
void C786Cpu_pushData16(C786Cpu*, Uint16);
Uint16 C786Cpu_popData16(C786Cpu*);
void C786Cpu_pushData32(C786Cpu*, Uint32);
Uint32 C786Cpu_popData32(C786Cpu*);

Uint8 C786Cpu_fetchData8(C786Cpu*);
Uint16 C786Cpu_fetchData16(C786Cpu*);
Uint32 C786Cpu_fetchData32(C786Cpu*);


/*****************************************************************************
* Memory Data Address Translator
*/

Uint32 C786Cpu_translateDataAdr(C786Cpu*, Uint32);
Uint32 C786Cpu_translateStackAdr(C786Cpu*, Uint32);
Uint32 C786Cpu_translateCodeAdr(C786Cpu*, Uint32);


#endif // C786_CPU_MEMORY_H_INCLUDED
