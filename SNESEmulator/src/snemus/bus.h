#ifndef snemus_bus_h
#define snemus_bus_h

#ifndef snesmus_emulation_h
typedef struct SMEmulator SMEmulator;
#endif

typedef struct SMBus SMBus;

#include "api.h"
#include "emu.h"


struct SMBus{
	Uint8 l_data;
	
	Uint8 (*read)(SMBus *bus, Uint32 adr);
	void (*write)(SMBus *bus, Uint32 adr, Uint8 data);
	
	SMEmulator *emulator;
};

Uint8 SM_Bus_read(SMBus *bus, Uint32 adr);
void SM_Bus_write(SMBus *bus, Uint32 adr, Uint8 data);


#endif // snemus_bus_h
