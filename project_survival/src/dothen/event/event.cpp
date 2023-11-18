#include "event.h"

void DOTHENEvent::initializeEvent(){
	
	if(!static_DOTHENEvent::input_initialized){
		SDL_Init(SDL_INIT_EVENTS);
		
		static_DOTHENEvent::input_initialized = true;
	}
	
}

DOTHENEvent::DOTHENEvent(){
	this->initializeEvent();
}

DOTHENEvent::~DOTHENEvent(){
	
}

void DOTHENEvent::processEvents(){
	
	while(SDL_PollEvent(&this->sdl_event)){
		switch(this->sdl_event.type){
			case SDL_KEYDOWN:{
				if(this->onKeyDown){
					this->onKeyDown(this->sdl_event.key.keysym.sym, this->sdl_event.key.keysym.mod);
				}
			}
			break;
			case SDL_KEYUP:{
				if(this->onKeyUp){
					this->onKeyUp(this->sdl_event.key.keysym.sym, this->sdl_event.key.keysym.mod);
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:{
				if(this->onMouseButtonDown){
					this->onMouseButtonDown(this->sdl_event.button.button, this->sdl_event.motion.x, this->sdl_event.motion.y);
				}
			}
			break;
			case SDL_MOUSEBUTTONUP:{
				if(this->onMouseButtonUp){
					this->onMouseButtonUp(this->sdl_event.button.button, this->sdl_event.motion.x, this->sdl_event.motion.y);
				}
			}
			break;
			case SDL_MOUSEMOTION:{
				if(this->onMouseMotion){
					this->onMouseMotion(this->sdl_event.motion.x, this->sdl_event.motion.y, this->sdl_event.motion.xrel, this->sdl_event.motion.yrel);
				}
			}
			break;
			case SDL_MOUSEWHEEL:{
				if(this->onMouseWheel){
					this->onMouseWheel(this->sdl_event.wheel.x, this->sdl_event.wheel.y);
				}
			}
			break;
			case SDL_FINGERDOWN:{
				if(this->onFingerDown){
					this->onFingerDown(this->sdl_event.tfinger.touchId, this->sdl_event.tfinger.x, this->sdl_event.tfinger.y);
				}
			}
			break;
			case SDL_FINGERUP:{
				if(this->onFingerUp){
					this->onFingerUp(this->sdl_event.tfinger.touchId, this->sdl_event.tfinger.x, this->sdl_event.tfinger.y);
				}
			}
			break;
			case SDL_FINGERMOTION:{
				if(this->onFingerMotion){
					this->onFingerMotion(this->sdl_event.tfinger.touchId, this->sdl_event.tfinger.x, this->sdl_event.tfinger.y, this->sdl_event.tfinger.dx, this->sdl_event.tfinger.dy);
				}
			}
			break;
			case SDL_QUIT:{
				if(this->onQuit){
					this->onQuit();
				}
			}
			break;
			default:{
				
			}
		}
	}
	
}
