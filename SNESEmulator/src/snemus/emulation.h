#ifndef snemus_emulation_h
#define snemus_emulation_h

#include <stdio.h>
#include <stdlib.h>

#include "emu.h"


#define NOT_IMPLEMENTED(feature) {\
		printf("\n\n\tNOT IMPLEMENTED: "#feature);\
		exit(0);\
	}

#define NOT_IMPLEMENTED_NUMERIC(feature, value) {\
		printf("\n\n\tNOT IMPLEMENTED: "#feature, value);\
		exit(0);\
	}

struct SMEmulator{
	SMBus *bus;
	SMCpu cpu;
	SMVideo video;
	
	/* Properties */
	Bool running;
	Uint32 cycles_cout;
};

void SM_Emu_init(SMEmulator *m_emu, SMBus *bus);

void SM_Emu_emuCycles(SMCpu *m_cpu, Uint8 cpu_cycles);

void SM_Emu_start(SMEmulator *m_emu);

void SM_Cpu_dumpBus(SMCpu *m_cpu, const Char* path);


#endif // snemus_emulation_h
