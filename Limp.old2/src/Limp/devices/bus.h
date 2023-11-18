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


#endif
