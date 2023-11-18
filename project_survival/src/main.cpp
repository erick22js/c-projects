#include <stdio.h>
#include <stdlib.h>

#include "dothen/dothen.h"

void onquitevent(){
	printf("Quit!\n");
}

void onclick(Uint8_t button, Int32_t x, Int32_t y){
	printf("Click at %d and %d!\n", x, y);
}

void keydown(Uint32_t code, Uint16_t mod){
	printf("Key press!\n");
}

Int_t dothen_main(){
	
	
	
	DOTHENWindow *wnd = new DOTHENWindow("Minha super Janela!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 480);
	DOTHENRendererContext *ctx = new DOTHENRendererContext(wnd);
	
	DOTHENRenderer2D *red2 = new DOTHENRenderer2D(ctx);
	DOTHENRenderer3D *red3 = new DOTHENRenderer3D(ctx);
	
	DOTHENEvent *ev = new DOTHENEvent();
	
	ev->onQuit = &onquitevent;
	ev->onMouseButtonDown = &onclick;
	ev->onKeyDown = &keydown;
	
	while(true){
		ev->processEvents();
		
	}
	
	delete ctx;
	
	delete wnd;
	
	/*
	bool valor = true;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	
	bool running = 1;
	
	SDL_Event ev;
	SDL_Window *wd = SDL_CreateWindow("Ola SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	SDL_GLContext ctx = SDL_GL_CreateContext(wd);
	
	glewInit();
	
	if(init()){
		printf("Error in Program initializing!");
	}
	else{
		while(running){
			while(SDL_PollEvent(&ev)){
				if(ev.type==SDL_QUIT){
					running = 0;
				}
			}
			int wid, hei;
			SDL_GetWindowSize(wd, &wid, &hei);
			glViewport(0, 0, wid, hei);
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			update();
			
			SDL_GL_SwapWindow(wd);
		}
	}
	
	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(wd);
	
	*/
	
	return 0;
}
