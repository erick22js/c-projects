/*****************************************************************************
* Product: I486 CPU 
* Version: 0.0
* Updated: Jan 01 2022
*****************************************************************************/
#ifndef I486_CPU_H_INCLUDED
#define I486_CPU_H_INCLUDED

struct I486cpu;
typedef struct I486cpu I486Cpu;

#include "../memory/bus.h"
#include "register.h"
#include "msegment.h"
#include "mpage.h"

/*****************************************************************************
*
* CPU
*
*****************************************************************************/
struct I486cpu{
    /* Registers in architeture --------------------------------------------*/
    struct I486regs{
        /* General Registers -----------------------------------------------*/
        Uint32 eax;
        Uint32 edx;
        Uint32 ebx;
        Uint32 ecx;
        Uint32 ebp;
        Uint32 esi;
        Uint32 edi;
        Uint32 esp;
        
        /* Segment Registers -----------------------------------------------*/
        Uint16 cs;
        Uint16 ss;
        Uint16 ds;
        Uint16 es;
        Uint16 fs;
        Uint16 gs;
        
        /* Status and Control Registers ------------------------------------*/
        Uint32 eflags;
        Uint32 eip;
        
        /* Memory Managment Registers --------------------------------------*/
        I486Segd gdtr;
        I486Segd ldtr;
        I486Segd idtr;
        I486Segd tr;
        /*
        Uint32 gdtr_base_address;
        Uint32 gdtr_limit;//:20;
        Uint32 idtr_base_address;
        Uint32 idtr_limit;//:20;
        Uint16 ldtr;
        Uint32 ldtr_base_address;
        Uint32 ldtr_limit;//:20;
        Uint16 ldtr_access;//:12;
        Uint16 tr;
        Uint32 tr_base_address;
        Uint32 tr_limit;//:20;
        Uint16 tr_access;//:12;
        */
        
        /* Control Registers -----------------------------------------------*/
        Uint32 cr0;
        Uint32 cr1;
        Uint32 cr2;
        Uint32 cr3;
        
        /* Test Registers --------------------------------------------------*/
        Uint32 dr0;
        Uint32 dr1;
        Uint32 dr2;
        Uint32 dr3;
        Uint32 dr4;
        Uint32 dr5;
        Uint32 dr6;
        Uint32 dr7;
        Uint32 tr3;
        Uint32 tr4;
        Uint32 tr5;
        Uint32 tr6;
        Uint32 tr7;
    }regs;
    
    /* Attached devices ----------------------------------------------------*/
    I486Bus *device_bus;
};


I486Cpu *I486Cpu_create(I486Bus *bus);
void I486Cpu_destroy(I486Cpu *);


#endif // I486_CPU_H_INCLUDED
