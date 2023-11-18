/*****************************************************************************
* Product: C786 CPU 
* Version: 0.0
* Updated: Jan 01 2022
*****************************************************************************/
#ifndef C786_CPU_H_INCLUDED
#define C786_CPU_H_INCLUDED

struct C786cpu;
typedef struct C786cpu C786Cpu;

#include "../memory/bus.h"
#include "register.h"
#include "msegment.h"
#include "mpage.h"

/*****************************************************************************
*
* CPU
*
*****************************************************************************/

struct C786cpu{
    /* Registers in architeture --------------------------------------------*/
    struct C786regs{
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
        C786Segd gdtr;
        C786Segd ldtr;
        C786Segd idtr;
        C786Segd tr;
        
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
    C786Bus *device_bus;
};


C786Cpu *C786Cpu_create(C786Bus *bus);
void C786Cpu_destroy(C786Cpu *);


#endif // C786_CPU_H_INCLUDED
