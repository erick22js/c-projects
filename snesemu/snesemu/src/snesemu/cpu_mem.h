#include "cpu_proc.h"

/*
	Memory Access Functions
*/

uint8 cpuReadMem8(uint32 adr){
	return busRead(adr);
}

void cpuWriteMem8(uint32 adr, uint8 data){
	busWrite(adr, data);
}

uint16 cpuReadMem16(uint32 adr){
	return busRead(adr) | (busRead(adr+1) << 8);
}

void cpuWriteMem16(uint32 adr, uint16 data){
	busWrite(adr, data);
	busWrite(adr+1, data>>8);
}


/*
	Code Fetching Functions
*/

void cpuFetch(){

}

