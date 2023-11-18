#ifndef limpasm_error_h
#define limpasm_error_h

#include <setjmp.h>

#include "laapi.h"

jmp_buf _LA_ERRJUMP;
void *_LA_ERROBJ;
Luint32 _LA_ERRDATA[4];
Lbool _LA_ERRENABLE = TRUE;

#define LA_THROWERR(code){\
		if(_LA_ERRENABLE){\
			printf("\n##&&## Error throwed at src file \"%s\" at line %d ##&&##\n", __FILE__, __LINE__);\
			longjmp(_LA_ERRJUMP, code);\
		}\
	}

/* Unexpected token */
#define LAERR_UNEXPECTEDTOKEN 0x1000


#endif