#ifndef limpasm_isa_database04_h
#define limpasm_isa_database04_h

#include "template.h"


/**
		JMP
*/
#define LAOPC_JMP_ido 0x0E
#define LAOPC_JMP_fro 0x0F
	
	{
		"jmp", 3,
		{
			{
				lfIDO, LAOPC_JMP_ido, 0, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFRO, LAOPC_JMP_fro, 0, 0,
				{
					{ laIMM32, liEDI },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFRO, LAOPC_JMP_fro, 1, 0,
				{
					{ laR32, liREGD },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
		JMPR
*/
#define LAOPC_JMPR_ido 0x10
#define LAOPC_JMPR_fro 0x0F
	
	{
		"jmpr", 3,
		{
			{
				lfIDO, LAOPC_JMPR_ido, 0, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFRO, LAOPC_JMPR_fro, 2, 0,
				{
					{ laIMM32, liEDI },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFRO, LAOPC_JMPR_fro, 3, 0,
				{
					{ laR32, liREGD },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

/**
		JR
*/
#define LAOPC_JEQ_fur 0x11
#define LAOPC_JNE_fur 0x11
	
	{
		"jeq", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 0, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 16, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jne", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 1, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 17, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jlt", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 2, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 18, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jgt", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 3, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 19, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jle", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 4, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 20, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jge", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 5, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 21, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jbl", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 6, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 22, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jab", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 7, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 23, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jbe", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 8, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 24, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jae", 2,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 9, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
			{
				lfFUR, LAOPC_JEQ_fur, 25, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jez", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 10, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jnz", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 11, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jltz", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 12, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jgtz", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 13, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jlez", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 14, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jgez", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 15, 0,
				{
					{ laIMM, liEXTsd },
					{ laR32, liREGO },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jsv", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 26, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jcv", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 27, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jsc", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 28, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jcc", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 29, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jso", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 30, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	
	{
		"jco", 1,
		{
			{
				lfFUR, LAOPC_JEQ_fur, 31, 0,
				{
					{ laIMM, liEXTsd },
					{ laVOID, liVOID },
					{ laVOID, liVOID },
				}
				, 0xff, FALSE
			},
		}
	},
	

#endif
