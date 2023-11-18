#ifndef snemus_testbus_h
#define snemus_testbus_h

#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "emulation.h"
#include "registers.h"


/**
	LoROM Based Mapping
*/

Uint8 mem_wram[1024*128]; /* 128 KB Working RAM */
Uint8 mem_rom[1024*1024*16]; /* 16 MB ROM */
Uint32 mem_rom_size = 0;
Uint8 mem_registers[1024*24]; /* 24 KB <Simulate Low Registers Memory> */
Uint8 mem_sram[1024*64]; /* 64 KB Static RAM */

Uint8 testbus_read(SMBus *bus, Uint32 adr){
	Uint8 bank = aBank(adr);
	adr &= 0xffff;
	
	//printf("=read bus at 0x%x\n", adr);
	
	if(isBetween(bank, 0x00, 0x3F)||isBetween(bank, 0x80, 0xBF)){
		if(isBetween(adr, 0x0000, 0x1FFF)){
			return mem_wram[adr];
		}
		else if(isBetween(adr, 0x2000, 0x7FFF)){
			return SM_Reg_read(bus->emulator, adr-0x2000);
		}
		else if(isBetween(adr, 0x8000, 0xFFFF)){
			return mem_rom[(bank<<15)|(adr&0x7FFF)];
		}
	}
	else if(isBetween(bank, 0x40, 0x6F)||isBetween(bank, 0xC0, 0xEF)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			return mem_rom[(bank<<15)|adr];
		}
		else{
			return mem_rom[(bank<<15)|(adr&0x7FFF)];
		}
	}
	else if(isBetween(bank, 0x70, 0x7D)||isBetween(bank, 0xF0, 0xFD)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			return mem_sram[adr]; /* TODO */
		}
		else{
			return mem_rom[(bank<<15)|(adr&0x7FFF)];
		}
	}
	else if(bank==0x7E){
		if(isBetween(adr, 0x0000, 0x1FFF)){
			/* TODO */
		}
		/* TODO */
	}
	else if(bank==0x7F){
		/* TODO */
	}
	else if(isBetween(bank, 0xFE, 0xFF)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			return mem_sram[adr]; /* TODO */
		}
		else{
			return mem_rom[((bank&0x7F)<<15)|(adr&0x7FFF)];
		}
	}
	
	NOT_IMPLEMENTED_NUMERIC("BUS READ AT ADDRESS 0x%x", adr);
	
	return 0;
}

void testbus_write(SMBus *bus, Uint32 adr, Uint8 data){
	Uint8 bank = aBank(adr);
	adr &= 0xffff;
	
	//printf("=write bus data 0x%x at 0x%x\n", data, adr);
	
	if(isBetween(bank, 0x00, 0x3F)||isBetween(bank, 0x80, 0xBF)){
		if(isBetween(adr, 0x0000, 0x1FFF)){
			mem_wram[adr] = data;
			return;
		}
		else if(isBetween(adr, 0x2000, 0x7FFF)){
			SM_Reg_write(bus->emulator, adr-0x2000, data);
			return;
		}
		else if(isBetween(adr, 0x8000, 0xFFFF)){
			mem_rom[(bank<<15)|(adr&0x7FFF)] = data;
			return;
		}
	}
	else if(isBetween(bank, 0x40, 0x6F)||isBetween(bank, 0xC0, 0xEF)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			mem_rom[(bank<<15)|adr] = data;
			return;
		}
		else{
			mem_rom[(bank<<15)|(adr&0x7FFF)] = data;
			return;
		}
	}
	else if(isBetween(bank, 0x70, 0x7D)||isBetween(bank, 0xF0, 0xFD)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			mem_sram[adr] = data; /* TODO */
			return;
		}
		else{
			mem_rom[(bank<<15)|(adr&0x7FFF)] = data;
			return;
		}
	}
	else if(bank==0x7E){
		if(isBetween(adr, 0x0000, 0x1FFF)){
			/* TODO */
		}
		/* TODO */
	}
	else if(bank==0x7F){
		/* TODO */
	}
	else if(isBetween(bank, 0xFE, 0xFF)){
		if(isBetween(adr, 0x0000, 0x7FFF)){
			mem_sram[adr] = data; /* TODO */
			return;
		}
		else{
			mem_rom[((bank&0x7F)<<15)|(adr&0x7FFF)] = data;
			return;
		}
	}
	
	NOT_IMPLEMENTED_NUMERIC("BUS WRITE AT ADDRESS 0x%x", adr);
}


Bool testbus_loadcart(const char* path){
	FILE *file = fopen(path, "r");
	
	if(file==NULL){
		return FALSE;
	}
	
	fseek(file, 0, SEEK_END);
	Uint32 length = ftell(file);
	fseek(file, 0, SEEK_SET);
	mem_rom_size = length;
	
	fread(mem_rom, 1, length, file);
	fclose(file);
	
	return TRUE;
}


#endif // snemus_testbus_h
