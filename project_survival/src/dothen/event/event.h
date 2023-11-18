#ifndef DOTHEN_EVENT_H_INCLUDED
#define DOTHEN_EVENT_H_INCLUDED

#include "inputhanddler.h"


namespace static_DOTHENEvent{
	
	static Bool_t input_initialized = false;
	
}


class DOTHENEvent{
	
private:
	
	SDL_Event sdl_event;
	
	void initializeEvent();
	
public:
	
	/* Event Handdler events listener functions */
	
	void (*onQuit)() = null;
	
	void (*onKeyDown)(Uint32_t code, Uint16_t mod) = null;
	void (*onKeyUp)(Uint32_t code, Uint16_t mod) = null;
	
	void (*onMouseMotion)(Int32_t x, Int32_t y, Int32_t delta_x, Int32_t delta_y) = null;
	void (*onMouseButtonDown)(Uint8_t code, Int32_t x, Int32_t y) = null;
	void (*onMouseButtonUp)(Uint8_t code, Int32_t x, Int32_t y) = null;
	void (*onMouseWheel)(Int32_t x, Int32_t y) = null;
	
	void (*onFingerMotion)(Uint32_t id, Float32_t x, Float32_t y, Float32_t delta_x, Float32_t delta_y) = null;
	void (*onFingerDown)(Uint32_t id, Float32_t x, Float32_t y) = null;
	void (*onFingerUp)(Uint32_t id, Float32_t x, Float32_t y) = null;
	
	/* Event Handdler main functions */
	
	DOTHENEvent();
	
	~DOTHENEvent();
	
	void processEvents();
	
};


#endif // DOTHEN_EVENT_H_INCLUDED
