#ifndef DOTHEN_RENDERER_OBJECT2D_H_INCLUDED
#define DOTHEN_RENDERER_OBJECT2D_H_INCLUDED

#include "../math/math.h"

class DOTHENObject2D{
private:
	
	Mat3 transformation;
	
public:
	
	Vec2 position;
	Vec2 scale;
	Float_t rotation;
	
	DOTHENObject2D();
	
};

#endif // DOTHEN_RENDERER_OBJECT2D_H_INCLUDED
