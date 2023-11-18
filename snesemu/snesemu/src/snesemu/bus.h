#ifndef SNESEMU_BUS_H
#define SNESEMU_BUS_H

#include "common.h"


uint8 busRead(uint32 adr);
void busWrite(uint32 adr, uint8 data);


#endif