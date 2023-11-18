#ifndef limpasm_isa_database02_h
#define limpasm_isa_database02_h

#include "template.h"


/**
	STRD
*/
#define LAOPC_STRD_dro 0x02
#define LAOPC_STRD_fur 0x03
	
	{
		"strd", 9,
		{
			{
				lfDRO, LAOPC_STRD_dro, 0, 0,
				{
					{laR8, liRSD},
					{laR8, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 1, 0,
				{
					{laR16, liRSD},
					{laR16, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 2, 0,
				{
					{laR32, liRSD},
					{laR32, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 0,
				{
					{laIMM16, liEXT},
					{laR8, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 1,
				{
					{laIMM16, liEXT},
					{laR16, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 2,
				{
					{laIMM16, liEXT},
					{laR32, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 3,
				{
					{laIMM32, liEDI},
					{laR8, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 4,
				{
					{laIMM32, liEDI},
					{laR16, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOPC_STRD_dro, 3, 5,
				{
					{laIMM32, liEDI},
					{laR32, liREGD},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"strd", 10,
		{
			{
				lfFUR, LAOPC_STRD_fur, 0, 0,
				{
					{ laR32, liREGO },
					{ laIMM16, liEXT },
					{ laEBX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 1, 0,
				{
					{ laR32, liREGO },
					{ laIMM16, liEXT },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 2, 0,
				{
					{ laR32, liREGO },
					{ laIMM32, liEDI },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 3, 0,
				{
					{ laR32, liREGO },
					{ laIMM32, liEDI },
					{ laEBX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 4, 0,
				{
					{ laR32, liREGO },
					{ laIMM32, liEDI },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 5, 0,
				{
					{ laR32, liREGO },
					{ laEAX, liVOID },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 6, 0,
				{
					{ laR32, liREGO },
					{ laEAX, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 7, 0,
				{
					{ laR32, liREGO },
					{ laEDX, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 8, 0,
				{
					{ laEBX, liVOID },
					{ laR32, liREGO },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRD_fur, 9, 0,
				{
					{ laIMM32, liEDI },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
	STRW
*/
#define LAOPC_STRW_fur 0x03
	
	{
		"strw", 11,
		{
			{
				lfFUR, LAOPC_STRW_fur, 10, 0,
				{
					{ laR32, liREGO },
					{ laIMM16, liEXT },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 11, 0,
				{
					{ laR32, liREGO },
					{ laAX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 12, 0,
				{
					{ laR32, liREGO },
					{ laBX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 13, 0,
				{
					{ laR32, liREGO },
					{ laCX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 14, 0,
				{
					{ laR32, liREGO },
					{ laDX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 15, 0,
				{
					{ laR32, liREGO },
					{ laIMM16, liEXT },
					{ laEBX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 16, 0,
				{
					{ laR32, liREGO },
					{ laIMM16, liEXT },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 17, 0,
				{
					{ laIMM32, liEDI },
					{ laIMM16, liEXT },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 18, 0,
				{
					{ laIMM32, liEDI },
					{ laR16, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 19, 0,
				{
					{ laEBX, liVOID },
					{ laR16, liREGO },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 20, 0,
				{
					{ laEBX, liVOID },
					{ laR16, liREGO },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
	STRB
*/
#define LAOPC_STRB_fur 0x03
	
	{
		"strb", 11,
		{
			{
				lfFUR, LAOPC_STRW_fur, 21, 0,
				{
					{ laR32, liREGO },
					{ laIMM8, liEXT },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 22, 0,
				{
					{ laR32, liREGO },
					{ laAL, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 23, 0,
				{
					{ laR32, liREGO },
					{ laAH, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 24, 0,
				{
					{ laR32, liREGO },
					{ laDL, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 25, 0,
				{
					{ laR32, liREGO },
					{ laDH, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 26, 0,
				{
					{ laR32, liREGO },
					{ laIMM8, liEXT },
					{ laEBX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 27, 0,
				{
					{ laR32, liREGO },
					{ laIMM8, liEXT },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 28, 0,
				{
					{ laIMM32, liEDI },
					{ laIMM8, liEXT },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 29, 0,
				{
					{ laIMM32, liEDI },
					{ laAL, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 30, 0,
				{
					{ laEBX, liVOID },
					{ laAL, liREGO },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_STRW_fur, 31, 0,
				{
					{ laEBX, liVOID },
					{ laAL, liREGO },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
	LDMD
*/
#define LAOP_LDMD_dro 0x04
#define LAOP_LDMD_fur 0x05
	
	{
		"ldmd", 9,
		{
			{
				lfDRO, LAOP_LDMD_dro, 0, 0,
				{
					{laR8, liRSD},
					{laR8, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 1, 0,
				{
					{laR16, liRSD},
					{laR16, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 2, 0,
				{
					{laR32, liRSD},
					{laR32, liREGD},
					{laIMM16|laOPTIONAL, liEXT},
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 0,
				{
					{laR8, liREGD},
					{laIMM16, liEXT},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 1,
				{
					{laR16, liREGD},
					{laIMM16, liEXT},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 2,
				{
					{laR32, liREGD},
					{laIMM16, liEXT},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 3,
				{
					{laR8, liREGD},
					{laIMM32, liEDI},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 4,
				{
					{laR16, liREGD},
					{laIMM32, liEDI},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
			{
				lfDRO, LAOP_LDMD_dro, 3, 5,
				{
					{laR32, liREGD},
					{laIMM32, liEDI},
					{laVOID, liVOID}
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"ldmd", 2,
		{
			{
				lfFUR, LAOP_LDMD_fur, 16, 0,
				{
					{ laR32, liREGO },
					{ laEBX, liEXT },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMD_fur, 17, 0,
				{
					{ laR32, liREGO },
					{ laEBX, liVOID },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
	LDMW
*/
#define LAOP_LDMW_fur 0x05
	
	{
		"ldmw", 8,
		{
			{
				lfFUR, LAOP_LDMW_fur, 0, 0,
				{
					{ laR16, liREGO },
					{ laEBX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 1, 0,
				{
					{ laR16, liREGO },
					{ laEBX, liVOID },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 2, 0,
				{
					{ laR16, liREGO },
					{ laESP, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 3, 0,
				{
					{ laR16, liREGO },
					{ laEFP, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 4, 0,
				{
					{ laR16, liREGO },
					{ laIMM32, liEDI },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 5, 0,
				{
					{ laR16, liREGO },
					{ laEBX, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 6, 0,
				{
					{ laR16, liREGO },
					{ laESP, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMW_fur, 7, 0,
				{
					{ laR16, liREGO },
					{ laEFP, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
	LDMB
*/
#define LAOP_LDMB_fur 0x05
	
	{
		"ldmb", 8,
		{
			{
				lfFUR, LAOP_LDMB_fur, 8, 0,
				{
					{ laR8, liREGO },
					{ laEBX, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 9, 0,
				{
					{ laR8, liREGO },
					{ laEBX, liVOID },
					{ laECX, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 10, 0,
				{
					{ laR8, liREGO },
					{ laESP, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 11, 0,
				{
					{ laR8, liREGO },
					{ laEFP, liVOID },
					{ laIMM16|laOPTIONAL, liEXT },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 12, 0,
				{
					{ laR8, liREGO },
					{ laIMM32, liEDI },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 13, 0,
				{
					{ laR8, liREGO },
					{ laEBX, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 14, 0,
				{
					{ laR8, liREGO },
					{ laESP, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOP_LDMB_fur, 15, 0,
				{
					{ laR8, liREGO },
					{ laEFP, liVOID },
					{ laIMM32, liEDI },
				}
				, 0xff, FALSE
			},
		}
	},
	

#endif
