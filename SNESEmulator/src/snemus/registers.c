#include "registers.h"


Uint8 SM_Reg_read(SMEmulator *m_emu, Uint16 adr){
	if(isBetween(adr, 0x2100, 0x2183)){
		return SMREG_Video_read(&m_emu->video, adr-0x2100);
	}
	return 0;
}

void SM_Reg_write(SMEmulator *m_emu, Uint16 adr, Uint8 data){
	if(isBetween(adr, 0x2100, 0x2183)){
		SMREG_Video_write(&m_emu->video, adr-0x2100, data);
		return;
	}
}

