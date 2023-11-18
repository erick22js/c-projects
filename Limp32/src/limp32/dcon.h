#ifndef LIMP32_DCON_H_INCLUDED
#define LIMP32_DCON_H_INCLUDED

#include "cpu/cpu.h"

/**
	DEVICE CONTROL INTERFACE
*/

struct _l32dcon{
	L32Cpu *m_cpu;
};
typedef struct _l32dcon L32Dcon;

L32Dcon _l32dcon_blank = {};


#endif // LIMP32_DCON_H_INCLUDED
