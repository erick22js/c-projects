#ifndef UTIL_MEM_H_INCLUDED
#define UTIL_MEM_H_INCLUDED

#include <stdlib.h>

#define new(Type) ((Type*)malloc(sizeof(Type)))
#define new_arr(Type, length) ((Type*)malloc(sizeof(Type)*length))

#define delete(obj) (free((void*)obj))

#endif // UTIL_MEM_H_INCLUDED
