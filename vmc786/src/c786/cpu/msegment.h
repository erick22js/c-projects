#ifndef C786_CPU_MSEGMENT_H_INCLUDED
#define C786_CPU_MSEGMENT_H_INCLUDED

#include "../types.h"

/*****************************************************************************
* Segment Descriptor Data Structure
*/

struct C786segd{
    Uint32 base_address;
    Uint32 limit;//:20;
    Uint16 access;//:12;
};
typedef struct C786segd C786Segd;

#include "memory.h"

#define _C786Seg_decode2segd(ldw, hdw, out_segd){\
        out_segd.base_address = ldw;\
        out_segd.limit = hdw&0xffff;\
        out_segd.access = hdw>>16;\
    }


/*****************************************************************************
* Cpu SEGMENTATION Translation Handdler
*/

#define _C786MSeg_accessSegment(l_cpu, logical_adr, seg_descriptor, linear_adr){\
        Uint32 limit = (seg_descriptor.limit)<<(seg_descriptor.access&0x800?16:0);\
        if(logical_adr>(seg_descriptor.limit)){\
            /*TODO: thrown a segmentation fault*/\
        }\
        else{\
            linear_adr = (seg_descriptor.base_address)+logical_adr;\
        }\
    }

Uint32 _C786MSeg_adr_logical2Linear(C786Cpu *, Uint32, Uint16);


#endif // C786_CPU_MSEGMENT_H_INCLUDED
