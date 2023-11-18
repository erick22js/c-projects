#ifndef limpasm_linkedlist_h
#define limpasm_linkedlist_h

#include <stdio.h>
#include <stdlib.h>

#include "laapi.h"


#define LA_DEF_LINKEDLIST(type, name)\
	struct _LALinkedList##name##Item;\
	typedef struct _LALinkedList##name##Item _LALinkedList##name##Item;\
	struct _LALinkedList##name##Item{\
		type value;\
		_LALinkedList##name##Item *next;\
	};\
	\
	typedef struct LALinkedList##name{\
		_LALinkedList##name##Item *first, *last, *actual;\
	}LALinkedList##name;\
	\
	void LA_LL##name##_init(LALinkedList##name* list){\
		list->first = NULL;\
		list->last = NULL;\
		list->actual = NULL;\
	}\
	void LA_LL##name##_push(LALinkedList##name* list, type value){\
		_LALinkedList##name##Item *item = (_LALinkedList##name##Item*)malloc(sizeof(_LALinkedList##name##Item));\
		item->value = value;\
		item->next = NULL;\
		if(list->last==NULL){\
			list->last = list->first = item;\
		}\
		else{\
			list->last->next = item;\
			list->last = item;\
		}\
	}\
	void LA_LL##name##_first(LALinkedList##name* list){\
		list->actual = list->first;\
	}\
	type LA_LL##name##_actual(LALinkedList##name* list){\
		return list->actual->value;\
	}\
	Lbool LA_LL##name##_hasNext(LALinkedList##name* list){\
		return (list->actual!=NULL)&&(list->actual->next!=NULL);\
	}\
	void LA_LL##name##_next(LALinkedList##name* list){\
		if(list->actual!=NULL){\
			list->actual = list->actual->next;\
		}\
	}\
	

#endif
