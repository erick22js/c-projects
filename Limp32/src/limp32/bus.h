#ifndef LIMP32_BUS_H_INCLUDED
#define LIMP32_BUS_H_INCLUDED

#include "cpu/cpu.h"

/**
	MEMORY BUS ACCESS INTERFACE
*/

struct _l32bus{
	Bool busy; /// Signal for busy state bus
	Uint8 (*get8)(Uint32 adr);
	void (*set8)(Uint32 adr, Uint8 data);
	Uint16 (*get16)(Uint32 adr);
	void (*set16)(Uint32 adr, Uint16 data);
	Uint32 (*get32)(Uint32 adr);
	void (*set32)(Uint32 adr, Uint32 data);
};
typedef struct _l32bus L32Bus;

/// Functions: blank interfaces for bus operating

Uint8 _l32bus_get8(Uint32 adr){
	return 0;
}

void _l32bus_set8(Uint32 adr, Uint8 data){}

Uint16 _l32bus_get16(Uint32 adr){
	return 0;
}

void _l32bus_set16(Uint32 adr, Uint16 data){}

Uint32 _l32bus_get32(Uint32 adr){
	return 0;
}

void _l32bus_set32(Uint32 adr, Uint32 data){}

L32Bus _l32bus_blank = {
	&_l32bus_get8, &_l32bus_set8,
	&_l32bus_get16, &_l32bus_set16,
	&_l32bus_get32, &_l32bus_set32,
};


#endif // LIMP32_BUS_H_INCLUDED
