#ifndef snemus_api_h
#define snemus_api_h

#include <stdlib.h>


typedef char Char;

typedef _Bool Bool;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

typedef signed char Sint8;
typedef signed short Sint16;
typedef signed int Sint32;

#ifndef NULL
	#define NULL ((void*)0)
#endif

#define FALSE 0
#define TRUE 1


#define clearMem(ptr, size) memset(ptr, 0, size)


#define getBit(data, index) ((data>>index)&1)
#define setBit(opr, index) (opr|(1<<index))
#define clrBit(opr, index) (opr&(~(1<<index)))
#define invBit(opr, index) (opr^(1<<index))
#define putBit(opr, index, data) ((opr&(~(1<<index)))|(((data)!=0)<<index))

#define lowByte(word) (word&0xff)
#define highByte(word) ((word>>8)&0xff)
#define aBank(address) ((address>>16)&0xff)
#define replaceLowByte(word, lo) ((word&0xff00)|lo)
#define replaceHighByte(word, hi) ((word&0x00ff)|(hi<<8))

#define toWord(lo, hi) (lo|(hi<<8))
#define toAddress(word, bank) ((word)|(bank<<16))

#define toU8(data) ((Uint8)data)
#define toU16(data) ((Uint16)data)
#define toU32(data) ((Uint32)data)

#define toS8(data) ((Sint8)data)
#define toS16(data) ((Sint16)data)
#define toS32(data) ((Sint32)data)

#define isBetween(data, min, max) ((data>=min)&&(data<=max))


#endif // snemus_api_h
