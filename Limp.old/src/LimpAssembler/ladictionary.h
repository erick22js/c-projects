#ifndef limpasm_dictionary_h
#define limpasm_dictionary_h

#include <stdio.h>
#include <stdlib.h>

#include "laapi.h"


#define LA_DEF_DICTIONARY(typeK, typeV, name, cmpKeyFunc)\
	typedef struct LADictionary##name{\
		struct _LADictionaryItem##name{\
			Lbool defined;\
			typeK key;\
			typeV value;\
		}*elements;\
		Luint32 index;\
		Luint32 capacity;\
		Luint32 remaining;\
	}LADictionary##name;\
	typedef struct _LADictionaryItem##name _LADictionaryItem##name;\
	void _LA_DC##name##_grow(LADictionary##name* dict){\
		Luint32 old_capacity = dict->capacity;\
		dict->remaining += dict->capacity;\
		dict->capacity *= 2;\
		_LADictionaryItem##name* reelements = (_LADictionaryItem##name*)realloc(dict->elements, dict->capacity*sizeof(_LADictionaryItem##name));\
		dict->elements = reelements;\
		for(Luint32 ei=old_capacity; ei<dict->capacity; ei++){\
			dict->elements[ei].defined = FALSE;\
		}\
	}\
	_LADictionaryItem##name* _LA_DC##name##_getItem(LADictionary##name* dict, typeK key){\
		_LADictionaryItem##name* avaItem = NULL;\
		Luint32 ei = 0;\
		if(dict->remaining<2){\
			_LA_DC##name##_grow(dict);\
		}\
		for(; ei<dict->capacity; ei++){\
			if(dict->elements[ei].defined){\
				if(cmpKeyFunc(dict->elements[ei].key, key)){\
					return &dict->elements[ei];\
				}\
			}\
			else{\
				if(avaItem==NULL){\
					avaItem = &dict->elements[ei];\
				}\
			}\
		}\
		if(avaItem!=NULL){\
			avaItem->defined = TRUE;\
			avaItem->key = key;\
			dict->remaining--;\
			return avaItem;\
		}\
		\
	}\
	Lbool LA_DC##name##_hasKey(LADictionary##name* dict, typeK key){\
		Luint32 ei = 0;\
		for(; ei<dict->capacity; ei++){\
			if(dict->elements[ei].defined){\
				if(dict->elements[ei].key==key){\
					return TRUE;\
				}\
			}\
		}\
		return FALSE;\
	}\
	void LA_DC##name##_init(LADictionary##name* dict){\
		dict->capacity = 2;\
		dict->remaining = dict->capacity;\
		_LADictionaryItem##name* elements = (_LADictionaryItem##name*)malloc(dict->capacity*sizeof(_LADictionaryItem##name));\
		dict->elements = elements;\
	}\
	void LA_DC##name##_set(LADictionary##name* dict, typeK key, typeV value){\
		_LA_DC##name##_getItem(dict, key)->value = value;\
	}\
	typeV LA_DC##name##_get(LADictionary##name* dict, typeK key){\
		return _LA_DC##name##_getItem(dict, key)->value;\
	}\
	typeV *LA_DC##name##_at(LADictionary##name* dict, typeK key){\
		return &_LA_DC##name##_getItem(dict, key)->value;\
	}\
	


#endif