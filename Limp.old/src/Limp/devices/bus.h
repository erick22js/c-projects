#ifndef limp_bus_h
#define limp_bus_h

struct LIMPBus;

#include "../api.h"


typedef struct LIMPBus{
	
	void *main; /* Main component */
	
	/* Bus data retrieve operation */
	
	Luint8 (*get8)(Luint32 adr);
	Luint16 (*get16)(Luint32 adr);
	Luint32 (*get32)(Luint32 adr);
	void (*set8)(Luint32 adr, Luint8 data);
	void (*set16)(Luint32 adr, Luint16 data);
	void (*set32)(Luint32 adr, Luint32 data);
	
}LIMPBus;

#define _LIMPBus_G_RAM_SIZE (1024*1024*4) //4MB

Luint8 _LIMPBus_g_ram[_LIMPBus_G_RAM_SIZE];

Luint8 _LIMPBus_g_get8(Luint32 adr){
	if(adr<_LIMPBus_G_RAM_SIZE){
		return
			_LIMPBus_g_ram[adr];
	}
	return 0;
}

Luint16 _LIMPBus_g_get16(Luint32 adr){
	adr &= ~1;
	if(adr<_LIMPBus_G_RAM_SIZE){
		return
			(_LIMPBus_g_ram[adr++])|
			(_LIMPBus_g_ram[adr]<<8)
			;
	}
	return 0;
}

Luint32 _LIMPBus_g_get32(Luint32 adr){
	adr &= ~3;
	if(adr<_LIMPBus_G_RAM_SIZE){
		return
			(_LIMPBus_g_ram[adr++])|
			(_LIMPBus_g_ram[adr++]<<8)|
			(_LIMPBus_g_ram[adr++]<<16)|
			(_LIMPBus_g_ram[adr]<<24)
			;
	}
	return 0;
}

void _LIMPBus_g_set8(Luint32 adr, Luint8 data){
	if(adr<_LIMPBus_G_RAM_SIZE){
		_LIMPBus_g_ram[adr] = data;
	}
}

void _LIMPBus_g_set16(Luint32 adr, Luint16 data){
	adr &= ~1;
	if(adr<_LIMPBus_G_RAM_SIZE){
		_LIMPBus_g_ram[adr++] = data;
		_LIMPBus_g_ram[adr] = data>>=8;
	}
}

void _LIMPBus_g_set32(Luint32 adr, Luint32 data){
	adr &= ~3;
	if(adr<_LIMPBus_G_RAM_SIZE){
		_LIMPBus_g_ram[adr++] = data;
		_LIMPBus_g_ram[adr++] = data>>=8;
		_LIMPBus_g_ram[adr++] = data>>=8;
		_LIMPBus_g_ram[adr] = data>>=8;
	}
}



/*
Luint8 _LIMPBus_g_get8(Luint32 adr){
	return 0;
}

Luint16 _LIMPBus_g_get16(Luint32 adr){
	return 0;
}

Luint32 _LIMPBus_g_get32(Luint32 adr){
	return 0;
}

void _LIMPBus_g_set8(Luint32 adr, Luint8 data){
	
}

void _LIMPBus_g_set16(Luint32 adr, Luint16 data){
	
}

void _LIMPBus_g_set32(Luint32 adr, Luint32 data){
	
}
*/

LIMPBus _LIMPBus_g = {
	NULL,
	_LIMPBus_g_get8, _LIMPBus_g_get16, _LIMPBus_g_get32,
	_LIMPBus_g_set8, _LIMPBus_g_set16, _LIMPBus_g_set32,
};


#endif