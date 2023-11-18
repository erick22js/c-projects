#ifndef limpasm_isa_database_template_h
#define limpasm_isa_database_template_h


#define LAOPCDTB_TP01(_mnemonic, _code1, _code2)\
		{\
			_mnemonic, 13,\
			{\
				{\
					lfDRO, _code1, 0, 0,\
					{\
						{laR8, liREGD},\
						{laR8, liRSD},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 1, 0,\
					{\
						{laR16, liREGD},\
						{laR16, liRSD},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 2, 0,\
					{\
						{laR32, liREGD},\
						{laR32, liRSD},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 0,\
					{\
						{laR8, liREGD},\
						{laIMM16, liEXT},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 1,\
					{\
						{laR16, liREGD},\
						{laIMM16, liEXT},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 2,\
					{\
						{laR32, liREGD},\
						{laIMM16, liEXT},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 3,\
					{\
						{laR8, liREGD},\
						{laIMM32, liEDI},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 4,\
					{\
						{laR16, liREGD},\
						{laIMM32, liEDI},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfDRO, _code1, 3, 5,\
					{\
						{laR32, liREGD},\
						{laIMM32, liEDI},\
						{laVOID, liVOID}\
					}\
					, 0xff, FALSE\
				},\
				{\
					lfMIO, _code2, 0, 0,\
					{\
						{laR32, liREGO},\
						{laIMM32, liEDI},\
						{laVOID, liVOID}\
					}\
					, 0x11, FALSE\
				},\
				{\
					lfMIO, _code2, 1, 0,\
					{\
						{laR32, liREGO},\
						{laR32, liREGB},\
						{laVOID, liVOID}\
					}\
					, 0x11, FALSE\
				},\
				{\
					lfMIO, _code2, 2, 0,\
					{\
						{laR32, liREGO},\
						{laR32, liREGB},\
						{laIMM32, liEDI}\
					}\
					, 0x21, TRUE\
				},\
				{\
					lfMIO, _code2, 3, 0,\
					{\
						{laR32, liREGO},\
						{laR32, liREGB},\
						{laR32, liREGI}\
					}\
					, 0x21, TRUE\
				},\
			}\
		},

#endif