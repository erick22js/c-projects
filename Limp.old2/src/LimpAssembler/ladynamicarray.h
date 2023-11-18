#ifndef limpasm_dynamicarray_h
#define limpasm_dynamicarray_h

#include <stdio.h>
#include <stdlib.h>

#include "laapi.h"


#define LA_DEF_DYNAMICARRAY(type, name)\
	typedef struct LADynamicArray##name{\
		type* elements;\
		Luint32 length;\
		Luint32 capacity;\
	}LADynamicArray##name;\
	void _LA_DA##name##_auto(LADynamicArray##name* array){\
		if(array->length>=(array->capacity-2)){\
			array->capacity *= 2;\
			type* reelements = (type*)realloc(array->elements, array->capacity*sizeof(type));\
			array->elements = reelements;\
		}\
		else if((array->length<((array->capacity*1)/3))&&(array->length>8)){\
			array->capacity /= 2;\
			type* reelements = (type*)realloc(array->elements, array->capacity*sizeof(type));\
			array->elements = reelements;\
		}\
	}\
	void LA_DA##name##_init(LADynamicArray##name* array){\
		array->length = 0;\
		array->capacity = 2;\
		type* elements = (type*)malloc(array->capacity*sizeof(type));\
		array->elements = elements;\
	}\
	void LA_DA##name##_push(LADynamicArray##name* array, type value){\
		_LA_DA##name##_auto(array);\
		array->elements[array->length] = value;\
		array->length++;\
	}\
	type LA_DA##name##_pop(LADynamicArray##name* array){\
		_LA_DA##name##_auto(array);\
		array->length--;\
		return array->elements[array->length];\
	}\
	void LA_DA##name##_set(LADynamicArray##name* array, Luint32 index, type value){\
		array->elements[index] = value;\
	}\
	type LA_DA##name##_get(LADynamicArray##name* array, Luint32 index){\
		return array->elements[index];\
	}\
	type *LA_DA##name##_at(LADynamicArray##name* array, Luint32 index){\
		return &array->elements[index];\
	}\
	type *LA_DA##name##_atLast(LADynamicArray##name* array){\
		return &array->elements[array->length-1];\
	}\
	


#endif