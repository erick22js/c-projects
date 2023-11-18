#ifndef limpasm_isa_encoder_h
#define limpasm_isa_encoder_h

#include <string.h>

#include "laisadtb.h"


/* RETURNS: LA_NOTOPC if is not opcode */

#define LA_NOTOPC 0xffffffff

Luint32 LIMPASM_IsaDec_toMnemonicIndex(Lchar* identifier){
	
	for(Luint32 mni=0; mni<_LA_ISADTB_LENGTH; mni++){
		
		if(strcmp(identifier, _LA_ISADTB[mni].mnemonic)==0){
			return mni;
		}
		
	}
	
	return LA_NOTOPC;
}


/* Returns LA_NOTREG if is not a register */

#define LA_NOTREG 0xffffffff

Luint32 LIMPASM_IsaDec_toRegisterIndex(Lchar* identifier){
	
	for(Luint32 rgi=0; rgi<_LA_ISAREG_LENGTH; rgi++){
		
		if(strcmp(identifier, _LA_ISAREG[rgi].name)==0){
			return rgi;
		}
		
	}
	
	return LA_NOTREG;
}


#include "latokens.h"


typedef struct LAInstruction{
	
	/*Lchar* mnemonic;*/
	Luint32 mni;
	
	struct LAInstructionArg{
		LAIDArgument type;
		Luint32 data;
	}a[3];
	
	Luint8 mad_fmt; /* Memory access Format */
	Lbool uses_sc; /* Uses scale for memory access */
	Luint32 scale; /* scale average */
	
}LAInstruction;


Lbool LIMPASM_IsaEnc_isTypeOf(LAIDArgument from, LAIDArgument to){
	
	Lbool optional = to&laOPTIONAL;
	
	from &= 0xff;
	to &= 0xff;
	
	if((from==laVOID)&&(optional)){
		return TRUE;
	}
	
	if(to==laVOID){
		return from==laVOID;
	}
	if(to==laREG){
		return (from>=laEAX)&&(from<=laREG);
	}
	if(to==laIMM){
		return (from>=laIMM8)&&(from<=laIMM);
	}
	if(to==laR32){
		return ((from>=laEAX)&&(from<=laESD))||(from==laR32);
	}
	if(to==laR16){
		return ((from>=laAX)&&(from<=laSD))||(from==laR16);
	}
	if(to==laR8){
		return ((from>=laAL)&&(from<=laBH))||(from==laR8);
	}
	return from==to;
}

LAIsaMneVary *LIMPASM_IsaEnc_search(Luint32 mni, LAIDArgument a0, LAIDArgument a1, LAIDArgument a2, Luint8 mad_fmt, Lbool uses_scaler){
	
	for(Luint32 vi=0; vi<_LA_ISADTB[mni].vary_count; vi++){
		LAIsaMneVary *vary = &_LA_ISADTB[mni].vary[vi];
		
		/* Comparates the arguments types for identity approach */
		
		if(((mad_fmt!=0xff)&&(vary->format!=lfMIO))){
			continue;
		}
		
		if((mad_fmt!=0xff)&&(vary->mad_fmt!=mad_fmt)){
			continue;
		}
		
		if(vary->uses_sc!=uses_scaler){
			continue;
		}
		if(!LIMPASM_IsaEnc_isTypeOf(a0, vary->a[0].dtype)){
			continue;
		}
		if(!LIMPASM_IsaEnc_isTypeOf(a1, vary->a[1].dtype)){
			continue;
		}
		if(!LIMPASM_IsaEnc_isTypeOf(a2, vary->a[2].dtype)){
			continue;
		}
		
		printf("$$ ACCEPTED!!!! $$\n");
		return vary;
	}
	
	return NULL;
}

/* Returns TRUE if instruction have valid format, otherwise, returns FALSE */

Lbool LIMPASM_IsaEnc_encode(LAInstruction *instruction, Luint32* buffer, Luint32 *seek){
	LAIsaMneVary *varyant = LIMPASM_IsaEnc_search(instruction->mni, instruction->a[0].type, instruction->a[1].type, instruction->a[2].type, instruction->mad_fmt, instruction->uses_sc);
	
	printf("$$ INSTRUCTION COMPARATE (inst)$$\n");
	printf("\tmad_fmt: %d\n", instruction->mad_fmt);
	printf("\tuses_sc: %d\n", instruction->uses_sc);
	printf("\tArg0.type: %d\n", instruction->a[0].type);
	printf("\tArg1.type: %d\n", instruction->a[1].type);
	printf("\tArg2.type: %d\n", instruction->a[2].type);
	
	/* TODO: error => Invalid Instruction format */
	if(varyant==NULL){
		return FALSE;
	}
	
	printf("$$ VARYANT RETRIEVED (vary)$$\n");
	printf("\tmad_fmt: %d\n", varyant->mad_fmt);
	printf("\tuses_sc: %d\n", varyant->uses_sc);
	printf("\tArg0.type: %d\n", varyant->a[0].dtype);
	printf("\tArg1.type: %d\n", varyant->a[1].dtype);
	printf("\tArg2.type: %d\n", varyant->a[2].dtype);
	
	if(varyant==NULL){
		return FALSE;
	}
	
	Luint32 *opcode = &buffer[*seek];
	*seek += 4;
	
	/* Encodes liOPC */
	
	*opcode |= (varyant->opcode&0xff)<<24;
	
	switch(varyant->format){
		case lfDRO:{
			
			/* Encodes liOPR */
			*opcode |= (varyant->func_1&0x3)<<22;
			
			/* Encodes liRSD */
			if(varyant->func_1>=3){
				*opcode |= (varyant->func_2&0x7)<<19;
			}
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liRSD:{
						*opcode |= (instruction->a[ai].data&0x7)<<19;
					}
					break;
					case liREGD:{
						*opcode |= (instruction->a[ai].data&0x7)<<16;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0xffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0xffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0xffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfURO:{
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liREGS:{
						*opcode |= (instruction->a[ai].data&0x7)<<21;
					}
					break;
					case liREGD:{
						*opcode |= (instruction->a[ai].data&0x7)<<18;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0x3ffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0x3ffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0x3ffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfIDO:{
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0xffffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0xffffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0xffffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfIFO:{
			
			/* Encodes liFUNC */
			*opcode |= (varyant->func_1&0xf)<<20;
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0xfffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0xfffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0xfffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfDFR:{
			
			/* Encodes liTM */
			*opcode |= (varyant->func_1&0x3)<<22;
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liREGS:{
						*opcode |= (instruction->a[ai].data&0x7)<<19;
					}
					break;
					case liREGD:{
						*opcode |= (instruction->a[ai].data&0x7)<<16;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0xffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0xffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0xffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfFRO:{
			
			/* Encodes liFRO */
			*opcode |= (varyant->func_1&0x1f)<<19;
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liREGS:{
						*opcode |= (instruction->a[ai].data&0x7)<<16;
					}
					break;
					case liREGD:{
						*opcode |= (instruction->a[ai].data&0x7)<<13;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0x1fff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0x1fff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0x1fff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfFUR:{
			
			/* Encodes liFUR */
			*opcode |= (varyant->func_1&0x1f)<<19;
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liREGO:{
						*opcode |= (instruction->a[ai].data&0x7)<<16;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0xffff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0xffff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0xffff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
		case lfMIO:{
			
			/* Encodes liADM */
			*opcode |= (varyant->func_1&0x3)<<22;
			
			/* Encodes liSC */
			if(varyant->uses_sc){
				*opcode |= (instruction->scale&0x3)<<11;
			}
			
			/* Encodes Arguments */
			for(int ai=0; ai<3; ai++){
				
				switch(varyant->a[ai].encode){
					case liREGB:{
						*opcode |= (instruction->a[ai].data&0x7)<<19;
					}
					break;
					case liREGO:{
						*opcode |= (instruction->a[ai].data&0x7)<<16;
					}
					break;
					case liREGI:{
						*opcode |= (instruction->a[ai].data&0x7)<<13;
					}
					break;
					case liEXT:{
						*opcode |= (instruction->a[ai].data&0x3ff);
					}
					break;
					case liEXTsw:{
						*opcode |= ((instruction->a[ai].data>>1)&0x3ff);
					}
					break;
					case liEXTsd:{
						*opcode |= ((instruction->a[ai].data>>2)&0x3ff);
					}
					break;
					case liEDI:{
						buffer[(*seek)>>2] = instruction->a[ai].data;
						*seek += 4;
					}
					break;
					case liEDIsw:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>1;
						*seek += 4;
					}
					break;
					case liEDIsd:{
						buffer[(*seek)>>2] = instruction->a[ai].data>>2;
						*seek += 4;
					}
					break;
				}
				
			}
			
		}
		break;
	}
	
	return TRUE;
}

Luint32 LIMPASM_IsaEnc_size(LAInstruction *instruction){
	Luint32 size = 4;
	
	LAIsaMneVary *varyant = LIMPASM_IsaEnc_search(instruction->mni, instruction->a[0].type, instruction->a[1].type, instruction->a[2].type, instruction->mad_fmt, instruction->uses_sc);
	
	if(varyant==NULL){
		return 0;
	}
	
	for(int ai=0; ai<3; ai++){
		if((varyant->a[ai].encode==liEDI)||
			(varyant->a[ai].encode==liEDIsw)||
			(varyant->a[ai].encode==liEDIsd)){
			size += 4;
		}
	}
	
	return size;
}


#endif