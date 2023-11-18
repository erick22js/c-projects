#include "window.h"

void DOTHENWindow::initializeWindow(Char_t* title, Int_t x, Int_t y, Int_t w, Int_t h){
	if(!static_DOTHENWindow::video_initialized){
		SDL_Init(SDL_INIT_VIDEO);
		static_DOTHENWindow::video_initialized = true;
	}
	
	this->sdl_window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
}

void DOTHENWindow::terminateWindow(){
	SDL_DestroyWindow(this->sdl_window);
}

DOTHENWindow::DOTHENWindow(Char_t* title, Int_t x, Int_t y, Int_t w, Int_t h){
	this->initializeWindow(title, x, y, w, h);
}

DOTHENWindow::~DOTHENWindow(){
	this->terminateWindow();
}
