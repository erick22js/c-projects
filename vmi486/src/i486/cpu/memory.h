#ifndef I486_CPU_MEMORY_H_INCLUDED
#define I486_CPU_MEMORY_H_INCLUDED

#include "cpu.h"


/*****************************************************************************
* Bus Access
* Trivial for all cpu memory accesses
*/

#define _I486Cpu_getBus8(cpu, adr, out){\
        out = (Uint8)cpu->device_bus->get8(cpu->device_bus, adr);\
    }
#define _I486Cpu_setBus8(cpu, adr, in){\
        cpu->device_bus->set8(cpu->device_bus, adr, (Uint8)in);\
    }
#define _I486Cpu_getBus16(cpu, adr, out){\
        out = (Uint16)cpu->device_bus->get16(cpu->device_bus, adr);\
    }
#define _I486Cpu_setBus16(cpu, adr, in){\
        cpu->device_bus->set16(cpu->device_bus, adr, (Uint16)in);\
    }
#define _I486Cpu_getBus32(cpu, adr, out){\
        out = (Uint32)cpu->device_bus->get32(cpu->device_bus, adr);\
    }
#define _I486Cpu_setBus32(cpu, adr, in){\
        cpu->device_bus->set32(cpu->device_bus, adr, (Uint32)in);\
    }

#include "mpage.h"
#include "msegment.h"


/*****************************************************************************
* Memory Data Access
*/

void I486Cpu_setData8(I486Cpu*, Uint32, Uint8);
Uint8 I486Cpu_getData8(I486Cpu*, Uint32);
void I486Cpu_setData16(I486Cpu*, Uint32, Uint16);
Uint16 I486Cpu_getData16(I486Cpu*, Uint32);
void I486Cpu_setData32(I486Cpu*, Uint32, Uint32);
Uint32 I486Cpu_getData32(I486Cpu*, Uint32);

void I486Cpu_pushData8(I486Cpu*, Uint8);
Uint8 I486Cpu_popData8(I486Cpu*);
void I486Cpu_pushData16(I486Cpu*, Uint16);
Uint16 I486Cpu_popData16(I486Cpu*);
void I486Cpu_pushData32(I486Cpu*, Uint32);
Uint32 I486Cpu_popData32(I486Cpu*);

Uint8 I486Cpu_fetchData8(I486Cpu*);
Uint16 I486Cpu_fetchData16(I486Cpu*);
Uint32 I486Cpu_fetchData32(I486Cpu*);


/*****************************************************************************
* Memory Data Address Translator
*/

Uint32 I486Cpu_translateDataAdr(I486Cpu*, Uint32);
Uint32 I486Cpu_translateStackAdr(I486Cpu*, Uint32);
Uint32 I486Cpu_translateCodeAdr(I486Cpu*, Uint32);


#endif // I486_CPU_MEMORY_H_INCLUDED
