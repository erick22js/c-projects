#ifndef LIMP32_TIME_H_INCLUDED
#define LIMP32_TIME_H_INCLUDED

#include <windows.h>

#include "l_type.h"

/**
	INTERFACE FOR TIME STRUCT (MILISECONDS)
*/

union _L32time{
	struct _L32time32{
		Uint32 dwl, dwh;
	}dw;
	Uint64 qw;
};
typedef union _L32time L32Time;

/**
	RETRIEVES THE ACTUAL TIME IN MICROSECONDS FORMAT
*/

L32Time l32app_time_actual(){
	L32Time t_struct;
	
	FILETIME filetime;
	GetSystemTimeAsFileTime(&filetime);
	
	t_struct.dw.dwl = filetime.dwLowDateTime;
	t_struct.dw.dwh = filetime.dwHighDateTime;
	t_struct.qw /= 10;
	
	return t_struct;
}


#endif // LIMP32_TIME_H_INCLUDED
