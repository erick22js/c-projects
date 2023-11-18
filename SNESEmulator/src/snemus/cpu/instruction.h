#ifndef snemus_cpu_instruction_h
#define snemus_cpu_instruction_h

#include "adrmode.h"


typedef struct SMInstruction{
	void (*procedure)(SMCpu *m_cpu);
	const char *mnemonic;
	Uint8 cycles;
	SMAdrm adrmode;
	SMAdrmMod adrmmodifier;
}SMInstruction;


#include "procedure.h"


extern SMInstruction sm_instructions[256];


#endif // snemus_cpu_instruction_h
