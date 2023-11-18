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
	

#endif