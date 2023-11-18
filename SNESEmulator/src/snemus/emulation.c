#include <stdio.h>

#include "emulation.h"


void SM_Emu_init(SMEmulator *m_emu, SMBus *bus){
	/* Attach the bus to devices */
	bus->emulator = m_emu;
	m_emu->bus = bus;
	m_emu->cpu.io_bus = bus;
	
	/* Initializate the devices */
	SM_Video_init(&m_emu->video);
	SM_Cpu_restart(&m_emu->cpu);
	m_emu->cpu.emulator = m_emu;
	
	/* Properties */
	m_emu->cycles_cout = 0;
}

/*
	This Function Emulates CPU Cycling, wich is (without waitstates, short waitstates, joypad waitstates), repectively:
		- Master Cycles: 6; 8; 12
		- Clock: 1; 4/3; 2
		- Dot Cycles: 3/2; 2; 3
		
*/

void SM_Emu_emuCycles(SMCpu *m_cpu, Uint8 cpu_cycles){
	while(cpu_cycles){
		m_cpu->cycles_count++;
		Uint8 master_cycles = 6;
		while(master_cycles){
			SM_Video_tick(&m_cpu->emulator->video);
			master_cycles--;
		}
		cpu_cycles--;
	}
}

void SM_Emu_start(SMEmulator *m_emu){
	m_emu->running = TRUE;
	
	while(m_emu->running){
		SM_Cpu_step(&m_emu->cpu);
	}
}

void SM_Cpu_dumpBus(SMCpu *m_cpu, const Char* path){
	FILE *file = fopen(path, "w");
	
	if(file==NULL){
		return;
	}
	
	for(int bi=0; bi<1024*64; bi++){
		fputc(SM_Bus_read(m_cpu->io_bus, bi), file);
	}
	
	fclose(file);
}
