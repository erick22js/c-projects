#ifndef DOTHEN_MATH_VECTOR2_H_INCLUDED
#define DOTHEN_MATH_VECTOR2_H_INCLUDED

#include "math.h"

class Vec2{
public:
	
	Float_t x, y;
	
	Vec2(Float_t x, Float_t y);
	Vec2(Vec2 *vector);
	
	Vec2 *set(Float_t x, Float_t y);
	Vec2 *set(Vec2 *vector);
	
	Vec2 *translate(Float_t x, Float_t y);
	Vec2 *translate(Vec2 *vector);
	
	Vec2 *multiply(Float_t x, Float_t y);
	Vec2 *multiply(Vec2 *vector);
	
	Vec2 *scale(Float_t sc);
	
};

#endif // DOTHEN_MATH_VECTOR2_H_INCLUDED
