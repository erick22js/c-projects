#ifndef C786_BUS_H_INCLUDED
#define C786_BUS_H_INCLUDED

#include "../types.h"

/*****************************************************************************
*
* BUS
*
*****************************************************************************/
struct C786bus{
    /* Bus Functions Access ------------------------------------------------*/
    Uint8 (*get8)(struct C786bus*, Uint32);
    void (*set8)(struct C786bus*, Uint32, Uint8);
    Uint16 (*get16)(struct C786bus*, Uint32);
    void (*set16)(struct C786bus*, Uint32, Uint16);
    Uint32 (*get32)(struct C786bus*, Uint32);
    void (*set32)(struct C786bus*, Uint32, Uint32);
};

typedef struct C786bus C786Bus;

Uint8 _C786Bus_get8_null(C786Bus *, Uint32);
void _C786Bus_set8_null(C786Bus *, Uint32, Uint8);
Uint16 _C786Bus_get16_null(C786Bus *, Uint32);
void _C786Bus_set16_null(C786Bus *, Uint32, Uint16);
Uint32 _C786Bus_get32_null(C786Bus *, Uint32);
void _C786Bus_set32_null(C786Bus *, Uint32, Uint32);

C786Bus *C786Bus_create();
void C786Bus_destroy(C786Bus *);


#endif // C786_BUS_H_INCLUDED
