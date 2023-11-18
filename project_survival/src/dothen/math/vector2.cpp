#include "vector2.h"


Vec2::Vec2(Float_t x, Float_t y){
	this->x = x;
	this->y = y;
}

Vec2 *Vec2::set(Float_t x, Float_t y){
	this->x = x;
	this->y = y;
	return this;
}

Vec2 *Vec2::set(Vec2 *vector){
	this->x = vector->x;
	this->y = vector->y;
	return this;
}

Vec2 *Vec2::translate(Float_t x, Float_t y){
	this->x += x;
	this->y += y;
	return this;
}

Vec2 *Vec2::translate(Vec2 *vector){
	this->x += vector->x;
	this->y += vector->y;
	return this;
}

Vec2 *Vec2::multiply(Float_t x, Float_t y){
	this->x *= x;
	this->y *= y;
	return this;
}

Vec2 *Vec2::multiply(Vec2 *vector){
	this->x *= vector->x;
	this->y *= vector->y;
	return this;
}

Vec2 *Vec2::scale(Float_t sc){
	this->x *= sc;
	this->y *= sc;
	return this;
}
