#ifndef snemus_video_h
#define snemus_video_h

#include "display.h"
#include "regs.h"


typedef struct SMVideo{
	SMDisplay display;
	
	Uint8 regs[0x84];
	
	Uint32 cycles_count;
}SMVideo;

Uint8 SMREG_Video_read(SMVideo *video, Uint8 reg);
void SMREG_Video_write(SMVideo *video, Uint8 reg, Uint8 data);

void SM_Video_init(SMVideo *video);

void SM_Video_tick(SMVideo *video);



#endif // snemus_video_h
