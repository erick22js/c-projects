#include "context.h"

void DOTHENRendererContext::initializateContext(DOTHENWindow *window){
	if(!static_DOTHENRendererContext::glew_initialized){
		glewInit();
		static_DOTHENRendererContext::glew_initialized = true;
	}
	
	this->sdl_context = SDL_GL_CreateContext(window->sdl_window);
}

void DOTHENRendererContext::terminateContext(){
	SDL_GL_DeleteContext(this->sdl_context);
}

DOTHENRendererContext::DOTHENRendererContext(DOTHENWindow *window){
	this->window = window;
	this->initializateContext(window);
}

DOTHENRendererContext::~DOTHENRendererContext(){
	this->terminateContext();
}

void DOTHENRendererContext::flushScreen(){
	SDL_GL_SwapWindow(this->window->sdl_window);
}
