#ifndef limpasm_isa_database_h
#define limpasm_isa_database_h

#include "laapi.h"

typedef enum LAIDFormat{
	lfDRO,
	lfURO,
	lfIDO,
	lfIFO,
	lfDFR,
	lfFRO,
	lfFUR,
	lfMIO
}LAIDFormat;

typedef enum LAIDArgument{
	
	laVOID = 0,
	
	laEAX = 1, laEDX = 2, laECX = 3, laEBX = 4, laEFP = 5, laESP = 6, laESS = 7, laESD = 8,
	laAX = 9, laDX = 10, laCX = 11, laBX = 12, laFP = 13, laSP = 14, laSS = 15, laSD = 16,
	laAL = 17, laAH = 18, laDL = 19, laDH = 20, laCL = 21, laCH = 22, laBL = 23, laBH = 24,
	laR8 = 25, laR16 = 26, laR32 = 27, laREG = 28,
	laIMM8 = 32, laIMM16 = 33, laIMM32 = 34, laIMM = 35, laUNKNOWN = 36,
	
	laOPTIONAL = 256
	
}LAIDArgument;

typedef enum LAIDAEncode{
	
	liVOID,
	
	liOPC,
	liFUNC, liOPR, liTM,
	liRSD,
	liREGS, liREGD, liREGO, liREGB, liREGI,
	liEXT, liEXTsw, liEXTsd,
	liEDI, liEDIsw, liEDIsd
	
}LAIDAEncode;


struct LAReg{
	
	Lchar* name;
	Luint8 code;
	LAIDArgument type;
	LAIDArgument regtype;
	
}_LA_ISAREG[] = {
	{ "eax", 0, laEAX, laR32},
	{ "edx", 1, laEDX, laR32},
	{ "ecx", 2, laECX, laR32},
	{ "ebx", 3, laEBX, laR32},
	{ "efp", 4, laEFP, laR32},
	{ "esp", 5, laESP, laR32},
	{ "ess", 6, laESS, laR32},
	{ "esd", 7, laESD, laR32},
	{ "ax", 0, laAX, laR16},
	{ "dx", 1, laDX, laR16},
	{ "cx", 2, laCX, laR16},
	{ "bx", 3, laBX, laR16},
	{ "fp", 4, laFP, laR16},
	{ "sp", 5, laSP, laR16},
	{ "ss", 6, laSS, laR16},
	{ "sd", 7, laSD, laR16},
	{ "al", 0, laAL, laR8},
	{ "ah", 1, laAH, laR8},
	{ "dl", 2, laDL, laR8},
	{ "dh", 3, laDH, laR8},
	{ "cl", 4, laCL, laR8},
	{ "ch", 5, laCH, laR8},
	{ "bl", 6, laBL, laR8},
	{ "bh", 7, laBH, laR8},
};

const Luint32 _LA_ISAREG_LENGTH = sizeof(_LA_ISAREG)/sizeof(struct LAReg);


typedef struct LAIsaMneVary LAIsaMneVary;

struct LAIsaMne{
	
	const Lchar* mnemonic;
	Luint32 vary_count;
	
	struct LAIsaMneVary{
		
		LAIDFormat format;
		Luint8 opcode;
		Luint8 func_1;
		Luint8 func_2;
		
		struct LAIsaMneArg{
			LAIDArgument dtype;
			LAIDAEncode encode;
		}a[3];
		
		Luint8 mad_fmt;
		Lbool uses_sc;
		
	}vary[16];
	
}_LA_ISADTB[] = {
	
	#include "isadtb/isadtb01.h"
	#include "isadtb/isadtb02.h"
	#include "isadtb/isadtb03.h"
	
};

const Luint32 _LA_ISADTB_LENGTH = sizeof(_LA_ISADTB)/sizeof(struct LAIsaMne);


#endif