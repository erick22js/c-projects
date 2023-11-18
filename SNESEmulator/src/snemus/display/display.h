#ifndef snemus_display_h
#define snemus_display_h

#include <SDL2/SDL.h>

#include "../api.h"

#define SM_DISPLAY_WIDTH 256
#define SM_DISPLAY_HEIGHT 224

#define SM_DISPLAY_BUFFERSIZE (SM_DISPLAY_WIDTH*SM_DISPLAY_HEIGHT)

typedef struct SMDisplay{
	SDL_Window *window;
	SDL_Renderer *renderer;
	/*SDL_Surface *surface;*/
	SDL_Texture *view;
	
	SDL_Rect layout;
	
	Uint16 buffer[SM_DISPLAY_BUFFERSIZE];
}SMDisplay;


void SM_Display_init(SMDisplay *display);

void SM_Display_update(SMDisplay *display);


#endif // snemus_display_h
