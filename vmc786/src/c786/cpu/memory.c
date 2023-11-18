
#include "memory.h"

/*****************************************************************************
* Memory Data Access
*/

Uint8 C786Cpu_getData8(C786Cpu* l_cpu, Uint32 adr){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    Uint8 data = 0;
    _C786Cpu_getBus8(l_cpu, adr, data)
    return data;
}
void C786Cpu_setData8(C786Cpu* l_cpu, Uint32 adr, Uint8 data){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    _C786Cpu_setBus8(l_cpu, adr, data);
}
Uint16 C786Cpu_getData16(C786Cpu* l_cpu, Uint32 adr){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    Uint16 data = 0;
    _C786Cpu_getBus16(l_cpu, adr, data)
    return data;
}
void C786Cpu_setData16(C786Cpu* l_cpu, Uint32 adr, Uint16 data){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    _C786Cpu_setBus16(l_cpu, adr, data);
}
Uint32 C786Cpu_getData32(C786Cpu* l_cpu, Uint32 adr){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    Uint32 data = 0;
    _C786Cpu_getBus32(l_cpu, adr, data)
    return data;
}
void C786Cpu_setData32(C786Cpu* l_cpu, Uint32 adr, Uint32 data){
    adr = C786Cpu_translateDataAdr(l_cpu, adr);
    _C786Cpu_setBus32(l_cpu, adr, data);
}


/*****************************************************************************
* Memory Stack Access
*/

Uint8 C786Cpu_popData8(C786Cpu* l_cpu){
    l_cpu->regs.esp--;
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    Uint8 data;
    _C786Cpu_getBus8(l_cpu, adr, data);
    return 0;
}
void C786Cpu_pushData8(C786Cpu* l_cpu, Uint8 data){
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    _C786Cpu_setBus8(l_cpu, adr, data);
    l_cpu->regs.esp++;
}
Uint16 C786Cpu_popData16(C786Cpu* l_cpu){
    l_cpu->regs.esp -= 2;
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    Uint16 data;
    _C786Cpu_getBus16(l_cpu, adr, data);
    return 0;
}
void C786Cpu_pushData16(C786Cpu* l_cpu, Uint16 data){
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    _C786Cpu_setBus16(l_cpu, adr, data);
    l_cpu->regs.esp += 2;
}
Uint32 C786Cpu_popData32(C786Cpu* l_cpu){
    l_cpu->regs.esp -= 4;
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    Uint32 data;
    _C786Cpu_getBus32(l_cpu, adr, data);
    return 0;
}
void C786Cpu_pushData32(C786Cpu* l_cpu, Uint32 data){
    Uint32 adr = C786Cpu_translateStackAdr(l_cpu, l_cpu->regs.esp);
    _C786Cpu_setBus32(l_cpu, adr, data);
    l_cpu->regs.esp += 4;
}


/*****************************************************************************
* Memory Code Fetch Access
*/

Uint8 C786Cpu_fetchData8(C786Cpu* l_cpu){
    Uint32 adr = C786Cpu_translateCodeAdr(l_cpu, l_cpu->regs.eip);
    Uint8 data;
    _C786Cpu_getBus8(l_cpu, adr, data);
    l_cpu->regs.eip++;
    return 0;
}
Uint16 C786Cpu_fetchData16(C786Cpu* l_cpu){
    Uint32 adr = C786Cpu_translateCodeAdr(l_cpu, l_cpu->regs.eip);
    Uint16 data;
    _C786Cpu_getBus16(l_cpu, adr, data);
    l_cpu->regs.eip += 2;
    return 0;
}
Uint32 C786Cpu_fetchData32(C786Cpu* l_cpu){
    Uint32 adr = C786Cpu_translateCodeAdr(l_cpu, l_cpu->regs.eip);
    Uint32 data;
    _C786Cpu_getBus32(l_cpu, adr, data);
    l_cpu->regs.eip += 4;
    return 0;
}


/*****************************************************************************
* Memory Address Access Translator
*/

Uint32 C786Cpu_translateDataAdr(C786Cpu* l_cpu, Uint32 adr){
    adr = _C786MSeg_adr_logical2Linear(l_cpu, adr, _C786Cpu_getReg_ds(l_cpu));
    return adr;
}
Uint32 C786Cpu_translateStackAdr(C786Cpu* l_cpu, Uint32 adr){
    adr = _C786MSeg_adr_logical2Linear(l_cpu, adr, _C786Cpu_getReg_ss(l_cpu));
    return adr;
}
Uint32 C786Cpu_translateCodeAdr(C786Cpu* l_cpu, Uint32 adr){
    adr = _C786MSeg_adr_logical2Linear(l_cpu, adr, _C786Cpu_getReg_cs(l_cpu));
    return adr;
}

