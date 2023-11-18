#ifndef DOTHEN_MATH_VECTOR3_H_INCLUDED
#define DOTHEN_MATH_VECTOR3_H_INCLUDED

#include "math.h"

class Vec3{
public:
	
	Float_t x, y, z;
	
	Vec3(Float_t x, Float_t y, Float_t z);
	//Vec3(Vec3 vector);
	
	Vec3 *set(Float_t x, Float_t y, Float_t z);
	Vec3 *set(Vec3 *vector);
	
	Vec3 *translate(Float_t x, Float_t y, Float_t z);
	Vec3 *translate(Vec3 *vector);
	
	Vec3 *multiply(Float_t x, Float_t y, Float_t z);
	Vec3 *multiply(Vec3 *vector);
	
	Vec3 *scale(Float_t sc);
	
};

#endif // DOTHEN_MATH_VECTOR3_H_INCLUDED
