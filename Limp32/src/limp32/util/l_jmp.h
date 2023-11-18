#ifndef LIMP32_JMP_H_INCLUDED
#define LIMP32_JMP_H_INCLUDED

#include <setjmp.h>

#include "l_type.h"

/**
	INTERFACE FOR LONG JUMP
*/

#define L32APP_MAXJMPS 0xfff

struct _L32appjmp{
	jmp_buf buffer;
}_L32appjmps;

typedef struct _L32appjmp L32AppJmp;

/**
	LIMP32 APPLICATION LONG JUMP MODULES
*/

/// Function: jump to a setted buffer

void l32app_jmp_jmp(L32AppJmp *jmp, Uint32 code){
	longjmp(jmp->buffer, code);
}

/// Function: setup jump position
/// returns value on each jump operation, otherwise, returns zero

#define l32app_jmp_set(jmp)(setjmp((jmp)->buffer))


#endif // LIMP32_JMP_H_INCLUDED
