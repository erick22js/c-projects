#ifndef DOTHEN_RENDERER_OBJECT3D_H_INCLUDED
#define DOTHEN_RENDERER_OBJECT3D_H_INCLUDED

#include "../math/math.h"

class DOTHENObject3D{
private:
	
	Mat4 transformation;
	
public:
	
	Vec3 position;
	Vec3 scale;
	Vec3 rotation;
	
	DOTHENObject3D();
	
};

#endif // DOTHEN_RENDERER_OBJECT3D_H_INCLUDED
