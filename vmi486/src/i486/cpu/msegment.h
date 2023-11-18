#ifndef I486_CPU_MSEGMENT_H_INCLUDED
#define I486_CPU_MSEGMENT_H_INCLUDED

#include "memory.h"


/*****************************************************************************
* Segment Descriptor Data Structure
*/

struct I486segd{
    Uint32 base_address;
    Uint32 limit;//:20;
    Uint16 access;//:12;
};
typedef struct I486segd I486Segd;

#define _I486MSeg_decode2segd(ldword, hdword, out_segd){\
        out_segd.base_address = (hdword&0xff000000)|((hdword&0xff)<<16)|(ldword>>16);\
        out_segd.limit = (hdword&0xf0000)|(ldword&0xffff);\
        out_segd.access = ((hdword>>16)&0xf)|((hdword>>8)&0xff);\
    }


/*****************************************************************************
* Cpu SEGMENTATION Translation Handdler
*/




#endif // I486_CPU_MSEGMENT_H_INCLUDED
