#ifndef limpasm_parsemapcode_h
#define limpasm_parsemapcode_h

#include "laapi.h"
#include "ladynamicarray.h"
#include "ladictionary.h"
#include "laisadtb.h"


LA_DEF_DYNAMICARRAY(Luint8, ObjMap);

#define equalV(v1, v2) (v1==v2)
#define equalS(s1, s2) (strcmp(s1, s2)==0)

LA_DEF_DICTIONARY(Lchar*, Luint32, Const, equalV);

typedef Luint32 LOpcmPtr;


/**
	ENTRY MAP DESCRIPTOR
*/

typedef enum LAEntryType{
	
	leNULL = 0,
	leINST = 1, /* Instruction */
	leSDAT = 2 /* Static Data */
	
}LAEntryType;

typedef struct LAEntry{
	
	LOpcmPtr descriptor;
	LAEntryType type;
	
}LAEntry;

LA_DEF_DYNAMICARRAY(LAEntry, EntryMap);


/**
	OBJECT MAP DESCRIPTORS
*/

#define LA_PMC_pushObj2Map(obj_map, obj, out_ptr){\
		Luint8* buffer = (Luint8*)&obj;\
		for(int bi=0; bi<sizeof(obj); bi++){\
			LA_DAObjMap_push(obj_map, buffer[bi]);\
		}\
		out_ptr = (obj_map)->length-sizeof(obj);\
	}

#define LA_PMC_atObjMap(obj_map, pointer, _type)\
	((_type*)LA_DAObjMap_at(obj_map, pointer))

#define LA_PMC_pushEntry(entry_map, obj_map, entry, _type){\
		LAEntry edesc;\
		LA_PMC_pushObj2Map(obj_map, entry, edesc.descriptor);\
		edesc.type = _type;\
		LA_DAEntryMap_push(entry_map, edesc);\
	}


/**
	OPCMAP STRUCTS
*/

/* Value */

typedef enum LAIType{
	
	lsIMM8 = 0,
	lsIMM16 = 1,
	lsIMM32 = 2,
	lsIMM = 3,
	
}LAIType;

typedef struct LAValue{
	
	LAIType type;
	
	union LAValueData{
		
		Luint32 raw;
		
		Luint32 integer;
		Lsint32 sinteger;
		Lfloat32 fp;
		
		LOpcmPtr pointer;
		Lchar* string;
		
	}data;
	
	Lbool expression;
	Lbool identifier;
	Lbool string;
	
}LAValue;


/* Dictionary for Values */

LA_DEF_DICTIONARY(Lchar*, LAValue, V, equalV);


/* Expression */

typedef enum LAOperator{
	
	loMINUS = 0xf0, loNOT = 0xf1,
	
	loADD = 0x40, loSUB = 0x41,
	loMUL = 0x50, loDIV = 0x51, loMOD = 0x52,
	loAND = 0x10, loOR = 0x11, loXOR = 0x12,
	loLSH = 0x30, loRSH = 0x31,
	loEQ = 0x20, loNE = 0x21
	
}LAOperator;

typedef struct LAExpression{
	
	LAValue val1, val2;
	LAOperator opr;
	
}LAExpression;


/* Argument */

typedef struct LAArgument{
	
	LAIDArgument type;
	
	union LAArgData{
		
		LOpcmPtr value;
		Luint32 rgi;
		
	}data;
	
}LAArgument;


/* Entry Instruction */

/*
	arg_mad encoding
	 MSN     LSN
	[4-bit] [4-bit]
	 |       |
	 |       > Argument offset
	 |
	 > Number arguments
*/

typedef struct LAEntryInst{
	
	Luint8 mni; /* Mnemonic index */
	
	Luint8 args_n; /* Number of arguments */
	Luint8 args_mad; /* Memory Access disposition */
	Luint8 arg_sc; /* Scale argument */
	LAArgument args[4];
	
}LAEntryInst;


/* Entry static data */

typedef struct LAEntrySData{
	
	LOpcmPtr value;
	
	Lbool aligned;
	
}LAEntrySData;





#endif