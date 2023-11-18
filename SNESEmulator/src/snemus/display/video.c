#include "video.h"


Uint8 SMREG_Video_read(SMVideo *video, Uint8 reg){
	return video->regs[reg];
}
void SMREG_Video_write(SMVideo *video, Uint8 reg, Uint8 data){
	video->regs[reg] = data;
}

void SM_Video_init(SMVideo *video){
	SM_Display_init(&video->display);
	video->cycles_count = 0;
}

void SM_Video_tick(SMVideo *video){
	video->cycles_count++;
	if(video->cycles_count==4){
		video->cycles_count = 0;
		
		/*
			DISPLAY UPDATE TEST
		*/
		for(Uint32 i=0; i<SM_DISPLAY_WIDTH*SM_DISPLAY_HEIGHT; i++){
			video->display.buffer[i] = 0b1000000000000000;
			Uint8 blue = i&0xff;
			Uint8 red = i>>8;
			Uint8 green = (i>>9)+((i&0xff)>>1);
			video->display.buffer[i] |= ((blue>>3)&0b11111)|(((green>>3)&0b11111)<<5)|(((red>>3)&0b11111)<<10);
		}
		SM_Display_update(&video->display);
	}
}
