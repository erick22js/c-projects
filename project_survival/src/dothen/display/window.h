#ifndef DOTHEN_RENDERER_WINDOW_H_INCLUDED
#define DOTHEN_RENDERER_WINDOW_H_INCLUDED

#include <SDL2/SDL.h>

#include "../api.h"

namespace static_DOTHENWindow{
	
	static Bool_t video_initialized = false;
	
}

class DOTHENRendererContext;

class DOTHENWindow{
	friend class DOTHENRendererContext;
	
private:
	
	SDL_Window *sdl_window;
	
	void initializeWindow(Char_t* title, Int_t x, Int_t y, Int_t w, Int_t h);
	
	void terminateWindow();
	
public:
	
	DOTHENWindow(Char_t* title, Int_t x, Int_t y, Int_t w, Int_t h);
	
	~DOTHENWindow();
	
};



#endif // DOTHEN_RENDERER_WINDOW_H_INCLUDED
