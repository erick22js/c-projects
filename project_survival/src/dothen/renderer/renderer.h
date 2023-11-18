#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "../display/context.h"

class DOTHENRenderable;

class DOTHENRenderer{
	friend class DOTHENRenderable;
	
private:
	
	DOTHENRendererContext *context;
	
	virtual void processRenderer() = 0;
	
public:
	
	DOTHENRenderer(DOTHENRendererContext *context);
	
	~DOTHENRenderer();
	
	void render();
	
};

#endif // RENDERER_H_INCLUDED
