#ifndef snemus_registers_h
#define snemus_registers_h

#include "emulation.h"
#include "cpu/cpu.h"
#include "display/video.h"


Uint8 SM_Reg_read(SMEmulator *m_emu, Uint16 adr);

void SM_Reg_write(SMEmulator *m_emu, Uint16 adr, Uint8 data);


#endif // snemus_registers_h
