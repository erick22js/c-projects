#ifndef SNESEMU_COMMON_H
#define SNESEMU_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/*
	Types Definition
*/

typedef _Bool bool;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;


/*
	Values Definition
*/

#define true 1
#define false 0
#define null ((void*)0)


/*
	Util Functions
*/

#include <varargs.h>

#define log(...) (printf(__VA_ARGS__))

#define getBit(data, bit) (((data) >> (bit))&1)
#define setBit(data, bit, v) ((v)? (data)|(1 << (v)): (data)&(~(1 << (v))))


#endif