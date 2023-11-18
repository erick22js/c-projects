#include <stdio.h>
#include <stdlib.h>

#include "snemus/snemus.h"
#include "snemus/testbus.h"

const char* rom_path = "roms/SNES-master/CPUTest/CPU/MOV/CPUMOV.sfc";


int main(int argv, char* args[]){
	
	SMBus bus;
	bus.read = &testbus_read;
	bus.write = &testbus_write;
	
	SMEmulator emu;
	
	
	if(testbus_loadcart(rom_path)){
		printf("Successfull loaded rom with %d KB!\n\n", (mem_rom_size/1024));
	}
	else{
		printf("Error on loading function.\n\n");
	}
	
	SM_Emu_init(&emu, &bus);
	
	SM_Emu_start(&emu);
	
    return 0;
}
