#ifndef DOTHEN_RENDERER_CONTEXT_H_INCLUDED
#define DOTHEN_RENDERER_CONTEXT_H_INCLUDED

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "window.h"


namespace static_DOTHENRendererContext{
	
	static Bool_t glew_initialized = false;
	
}

class DOTHENRenderer;

class DOTHENRendererContext{
	
	friend class DOTHENRenderer;
	
private:
	
	DOTHENWindow *window;
	
	SDL_GLContext sdl_context;
		
	void initializateContext(DOTHENWindow *window);
	
	void terminateContext();
	
public:
	
	DOTHENRendererContext(DOTHENWindow *window);
	
	~DOTHENRendererContext();
	
	void flushScreen();
	
};



#endif // DOTHEN_RENDERER_CONTEXT_H_INCLUDED
