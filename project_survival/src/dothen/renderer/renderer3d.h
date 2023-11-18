#ifndef RENDERER3D_H_INCLUDED
#define RENDERER3D_H_INCLUDED

#include "renderer.h"


class DOTHENRenderer3D:public DOTHENRenderer{
	
private:
	
	void processRenderer();
	
public:
	
	DOTHENRenderer3D(DOTHENRendererContext *context);
	
	~DOTHENRenderer3D();
	
};


#endif // RENDERER2D_H_INCLUDED
