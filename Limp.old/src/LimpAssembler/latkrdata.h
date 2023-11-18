#ifndef limpasm_tokenerdata_h
#define limpasm_tokenerdata_h

#include <string.h>

#include "laapi.h"
#include "lalinkedlist.h"


Lchar* LA_TKRDATA_wrapString(Lchar* strsrc){
	Luint32 length = strlen(strsrc);
	Luint32 index = 0;
	Lchar* str = (Lchar*)malloc((length&(~3))+(length&3?4:0));
	
	while(index<length){
		str[index] = strsrc[index];
		index++;
	}
	while((index&3)!=3){
		str[index] = 0;
		index++;
	}
	
	str[index] = 0;
	
	return str;
}

LA_DEF_LINKEDLIST(Lchar*, Str);

#define LA_TKRDATA_toNumber(chr) (\
	(chr>='a'&&chr<='f')?chr-'a'+10:\
	(chr>='A'&&chr<='F')?chr-'A'+10:\
	(chr>='0'&&chr<='9')?chr-'0':0)
	

#define LA_TKRDATA_ISEOF(chr) ((chr==EOF)||(chr==0))

#define LA_TKRDATA_ISWHITE(chr) (((chr==' ')||(chr=='\t')||(chr<0x20))&&(chr!='\n'))

#define LA_TKRDATA_ISNAME(chr) ((chr>='a'&&chr<='z')||(chr>='A'&&chr<='Z')||(chr=='_')||(chr>='0'&&chr<='9'))

#define LA_TKRDATA_ISDECIMAL(chr) (chr>='0'&&chr<='9')

#define LA_TKRDATA_ISHEXADECIMAL(chr) ((chr>='a'&&chr<='f')||(chr>='A'&&chr<='F')||(chr>='0'&&chr<='9'))



#endif