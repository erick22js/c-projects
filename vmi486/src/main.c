#include <stdio.h>
#include <stdlib.h>

#include "i486/types.h"
#include "i486/cpu/cpu.h"

Uint8 mem[1024*1024*8];

Uint8 tb_get8(I486Bus*b, Uint32 adr){return *(mem+adr);}
void tb_set8(I486Bus*b, Uint32 adr, Uint8 data){*(mem+adr) = data;}
Uint16 tb_get16(I486Bus*b, Uint32 adr){return *((Uint16*)(mem+adr));}
void tb_set16(I486Bus*b, Uint32 adr, Uint16 data){*((Uint16*)(mem+adr)) = data;}
Uint32 tb_get32(I486Bus*b, Uint32 adr){return *((Uint32*)(mem+adr));}
void tb_set32(I486Bus*b, Uint32 adr, Uint32 data){*((Uint32*)(mem+adr)) = data;}

int main(){
    /*Setup initializers*/
    I486Bus *bus = I486Bus_create();
    bus->get8 = &tb_get8; bus->set8 = &tb_set8;
    bus->get16 = &tb_get16; bus->set16 = &tb_set16;
    bus->get32 = &tb_get32; bus->set32 = &tb_set32;
    I486Cpu *cpu = I486Cpu_create(bus);
    
    
    
    printf("Teste register: 0x%x\n", 0x0);
    
    system("pause");
    return 0;
}
