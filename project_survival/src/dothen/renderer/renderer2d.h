#ifndef RENDERER2D_H_INCLUDED
#define RENDERER2D_H_INCLUDED

#include "renderer.h"


class DOTHENRenderer2D:public DOTHENRenderer{
	
private:
	
	void processRenderer();
	
public:
	
	DOTHENRenderer2D(DOTHENRendererContext *context);
	
	~DOTHENRenderer2D();
	
};


#endif // RENDERER2D_H_INCLUDED
