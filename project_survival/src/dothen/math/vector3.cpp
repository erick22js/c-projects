#include "vector3.h"


Vec3::Vec3(Float_t x, Float_t y, Float_t z){
	this->x = x;
	this->y = y;
	this->z = z;
}
/*
Vec3::Vec3(Vec3 vector){
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}
*/
Vec3 *Vec3::set(Float_t x, Float_t y, Float_t z){
	this->x = x;
	this->y = y;
	this->z = z;
	return this;
}

Vec3 *Vec3::set(Vec3 *vector){
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
	return this;
}

Vec3 *Vec3::translate(Float_t x, Float_t y, Float_t z){
	this->x += x;
	this->y += y;
	this->z += z;
	return this;
}

Vec3 *Vec3::translate(Vec3 *vector){
	this->x += vector->x;
	this->y += vector->y;
	this->z += vector->z;
	return this;
}

Vec3 *Vec3::multiply(Float_t x, Float_t y, Float_t z){
	this->x *= x;
	this->y *= y;
	this->z *= z;
	return this;
}

Vec3 *Vec3::multiply(Vec3 *vector){
	this->x *= vector->x;
	this->y *= vector->y;
	this->z *= vector->z;
	return this;
}

Vec3 *Vec3::scale(Float_t sc){
	this->x *= sc;
	this->y *= sc;
	this->z *= sc;
	return this;
}
