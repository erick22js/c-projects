#ifndef SNESEMU_EMU_H
#define SNESEMU_EMU_H

#include "common.h"

/*
	Emulation State Properties
*/

struct{
	bool running;
}emu;


/*
	Emulation Control Functions
*/

void emuInit();
void emuRun();

#endif