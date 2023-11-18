#include "bus.h"


Uint8 SM_Bus_read(SMBus *bus, Uint32 adr){
	return bus->read(bus, adr);
}

void SM_Bus_write(SMBus *bus, Uint32 adr, Uint8 data){
	bus->write(bus, adr, data);
}

