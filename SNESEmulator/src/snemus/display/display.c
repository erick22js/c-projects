#include "display.h"


void SM_Display_init(SMDisplay *display){
	SDL_Init(SDL_INIT_VIDEO);
	display->window = SDL_CreateWindow("SNEMUS - SNES Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SM_DISPLAY_WIDTH*2, SM_DISPLAY_HEIGHT*2, SDL_WINDOW_RESIZABLE);
	display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
	/*display->surface = SDL_CreateRGBSurfaceWithFormat(0, SM_DISPLAY_WIDTH, SM_DISPLAY_HEIGHT, 16, SDL_PIXELFORMAT_XRGB1555);*/
	display->view = SDL_CreateTexture(display->renderer, SDL_PIXELFORMAT_XRGB1555, SDL_TEXTUREACCESS_STREAMING, SM_DISPLAY_WIDTH, SM_DISPLAY_HEIGHT);
	
	display->layout.x = 0;
	display->layout.y = 0;
	display->layout.w = SM_DISPLAY_WIDTH;
	display->layout.h = SM_DISPLAY_HEIGHT;
}

void SM_Display_update(SMDisplay *display){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:{
				SDL_DestroyWindow(display->window);
				exit(0);
			}
			break;
		}
	}
	/*SDL_LockTexture(display->view, NULL, NULL, NULL);*/
	SDL_UpdateTexture(display->view, NULL, display->buffer, SM_DISPLAY_WIDTH*2);
	SDL_RenderCopy(display->renderer, display->view, NULL, NULL);
	SDL_RenderPresent(display->renderer);
	/*SDL_UnlockTexture(display->view);*/
}

