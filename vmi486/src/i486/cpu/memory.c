
#include "memory.h"


/*****************************************************************************
* Memory Data Access
*/

Uint8 I486Cpu_getData8(I486Cpu* l_cpu, Uint32 adr){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    Uint8 data = 0;
    _I486Cpu_getBus8(l_cpu, adr, data)
    return data;
}
void I486Cpu_setData8(I486Cpu* l_cpu, Uint32 adr, Uint8 data){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    _I486Cpu_setBus8(l_cpu, adr, data);
}
Uint16 I486Cpu_getData16(I486Cpu* l_cpu, Uint32 adr){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    Uint16 data = 0;
    _I486Cpu_getBus16(l_cpu, adr, data)
    return data;
}
void I486Cpu_setData16(I486Cpu* l_cpu, Uint32 adr, Uint16 data){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    _I486Cpu_setBus16(l_cpu, adr, data);
}
Uint32 I486Cpu_getData32(I486Cpu* l_cpu, Uint32 adr){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    Uint32 data = 0;
    _I486Cpu_getBus32(l_cpu, adr, data)
    return data;
}
void I486Cpu_setData32(I486Cpu* l_cpu, Uint32 adr, Uint32 data){
    adr = I486Cpu_translateDataAdr(l_cpu, adr);
    _I486Cpu_setBus32(l_cpu, adr, data);
}

Uint8 I486Cpu_popData8(I486Cpu* l_cpu){
    return 0;
}
void I486Cpu_pushData8(I486Cpu* l_cpu, Uint8 data){
    
}
Uint16 I486Cpu_popData16(I486Cpu* l_cpu){
    return 0;
}
void I486Cpu_pushData16(I486Cpu* l_cpu, Uint16 data){
    
}
Uint32 I486Cpu_popData32(I486Cpu* l_cpu){
    return 0;
}
void I486Cpu_pushData32(I486Cpu* l_cpu, Uint32 data){
    
}

Uint8 I486Cpu_fetchData8(I486Cpu* l_cpu){
    return 0;
}
Uint16 I486Cpu_fetchData16(I486Cpu* l_cpu){
    return 0;
}
Uint32 I486Cpu_fetchData32(I486Cpu* l_cpu){
    return 0;
}


/*****************************************************************************
* Memory Address Access Translator
*/

Uint32 I486Cpu_translateDataAdr(I486Cpu* l_cpu, Uint32 adr){
    return adr;
}
Uint32 I486Cpu_translateStackAdr(I486Cpu* l_cpu, Uint32 adr){
    return adr;
}
Uint32 I486Cpu_translateCodeAdr(I486Cpu* l_cpu, Uint32 adr){
    return adr;
}

