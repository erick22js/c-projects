#ifndef LIMP32_CPU_H_INCLUDED
#define LIMP32_CPU_H_INCLUDED

/**
	LIMP32 CPU STRUCTURE
*/

struct _L32cpu;
typedef struct _L32cpu L32Cpu;

#include "../util/l_type.h"
#include "../bus.h"
#include "../dcon.h"

struct _L32cpu{
	struct _L32cpuregs{
		/// General Registers
		Uint32 eax;
		Uint32 edx;
		Uint32 ecx;
		Uint32 ebx;
		
		Uint32 esp;
		Uint32 efp;
		Uint32 ess;
		Uint32 esd;
		
		/// Control Registers
		Uint16 eip;		/// FETCHER RESERVED
		Uint32 efl_l;
		Uint32 efl_h;	/// FETCHER RESERVED
		Uint32 pdtr;	/// FETCHER RESERVED
		Uint32 psdtr;	/// FETCHER RESERVED
		Uint32 idtr;
		Uint32 tr;
		
		/// Test and Debug Registers
		Uint32 dboc;
		Uint32 dboi;
		Uint32 dbip;
		Uint32 dbpr;
	}regs;
	
	struct _L32cpustate{
		Bool running;
		Atomic(Bool) fetch_done;
		
		Bool waiting;
	}state;
	
	/// Attached devices controller
	L32Bus *devc_bus;
	L32Dcon *devc_dcon;
	
};


/**
	LIMP32 CPU MODULES
*/

#include "../util/l_time.h"
#include "../util/l_thread.h"
#include "register.h"
#include "flag.h"
#include "memory.h"


/// Function: Initializates a Limp32 CPU by his reference

void l32cpu(L32Cpu *l_cpu){
	
	/// Attach default devices
	l_cpu->devc_bus = &_l32bus_blank;
	l_cpu->devc_dcon = &_l32dcon_blank;
	
	/// Reset register values
	l_cpu->regs.eax = l_cpu->regs.edx = l_cpu->regs.ecx = l_cpu->regs.edx =
	l_cpu->regs.esp = l_cpu->regs.efp = l_cpu->regs.ess = l_cpu->regs.esd = 
	l_cpu->regs.eip = l_cpu->regs.efl_l = l_cpu->regs.efl_h =
	l_cpu->regs.pdtr = l_cpu->regs.psdtr = l_cpu->regs.idtr = l_cpu->regs.tr = 
	l_cpu->regs.dboc = l_cpu->regs.dboi = l_cpu->regs.dbip = l_cpu->regs.dbpr = 0;
	
	/// Reset cpu states
	l_cpu->state.running = false;
	l_cpu->state.fetch_done = false;
	
}


#endif // LIMP32_CPU_H_INCLUDED
