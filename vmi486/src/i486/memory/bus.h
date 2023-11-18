#ifndef I486_BUS_H_INCLUDED
#define I486_BUS_H_INCLUDED

#include "../types.h"

/*****************************************************************************
*
* BUS
*
*****************************************************************************/
struct I486bus{
    /* Bus Functions Access ------------------------------------------------*/
    Uint8 (*get8)(struct I486bus*, Uint32);
    void (*set8)(struct I486bus*, Uint32, Uint8);
    Uint16 (*get16)(struct I486bus*, Uint32);
    void (*set16)(struct I486bus*, Uint32, Uint16);
    Uint32 (*get32)(struct I486bus*, Uint32);
    void (*set32)(struct I486bus*, Uint32, Uint32);
};

typedef struct I486bus I486Bus;

Uint8 _I486Bus_get8_null(I486Bus *, Uint32);
void _I486Bus_set8_null(I486Bus *, Uint32, Uint8);
Uint16 _I486Bus_get16_null(I486Bus *, Uint32);
void _I486Bus_set16_null(I486Bus *, Uint32, Uint16);
Uint32 _I486Bus_get32_null(I486Bus *, Uint32);
void _I486Bus_set32_null(I486Bus *, Uint32, Uint32);

I486Bus *I486Bus_create();
void I486Bus_destroy(I486Bus *);


#endif // I486_BUS_H_INCLUDED
