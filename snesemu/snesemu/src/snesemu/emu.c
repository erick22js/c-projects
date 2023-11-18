#include "emu.h"
#include "cpu.h"


/*
	Emulation Control Functions
*/

void emuInit(){
	emu.running = false;

	cpuInit();
}

void emuRun(){
	emu.running = true;

	// A little loop execution
	for (int i=0; i<1; i++){
		cpuStep();
	}
}

