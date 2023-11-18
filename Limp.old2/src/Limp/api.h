#ifndef limp_api_h
#define limp_api_h


/**
	APPLICATION API INTERFACE
*/

/* Types definition */

typedef _Bool Bool_t;

typedef char Char_t;

typedef unsigned char Uint8_t;
typedef unsigned short Uint16_t;
typedef unsigned int Uint32_t;
typedef unsigned long long Uint64_t;

typedef signed char Sint8_t;
typedef signed short Sint16_t;
typedef signed int Sint32_t;
typedef signed long long Sint64_t;

typedef float Float32_t;
typedef double Float64_t;

#define Atomic(Type) _Atomic Type

#define NORETURN _Noreturn static

/* Values definition */

#ifndef NULL
	#define NULL
#endif

#define FALSE 0
#define TRUE 1


/**
	LIMP API INTERFACE
*/

/* Types definition */

typedef Bool_t Lbool;

typedef Char_t Lchar;

typedef Uint8_t Luint8;
typedef Uint16_t Luint16;
typedef Uint32_t Luint32;

typedef Sint8_t Lsint8;
typedef Sint16_t Lsint16;
typedef Sint32_t Lsint32;

typedef Float32_t Lfloat32;

/* Casts definition */

#define LBool(data) ((Lbool)(data))

#define LChar(data) ((Lchar)(data))

#define LUint8(data) ((Luint8)(data))
#define LUint16(data) ((Luint16)(data))
#define LUint32(data) ((Luint32)(data))

#define LSint8(data) ((Lsint8)(data))
#define LSint16(data) ((Lsint16)(data))
#define LSint32(data) ((Lsint32)(data))

#define LFloat32(data) ((Lfloat32)(data))

/* Values signed conversion */

#define L8T32(data) LUint32(LSint32(LSint8(LUint8(data))))
#define L16T32(data) LUint32(LSint32(LSint16(LUint16(data))))
#define L32T32(data) LUint32(data)
#define L8T16(data) LUint16(LSint16(LSint8(LUint8(data))))
#define L24T32(data) LUint32(((-LSint32(data>>23))&0xff000000)|(data&0xffffff))
#define L20T32(data) LUint32(((-LSint32(data>>19))&0xfff00000)|(data&0xfffff))

/**
	API MODULES DEFINITIONS
	
	LIMP => Main Limp Module
	L => Limp builtin types prefix
	LP => Limp extra util api
	LI => Limp internal Module
*/


#endif
