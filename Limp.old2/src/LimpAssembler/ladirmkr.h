#ifndef limpasm_dirmkr
#define limpasm_dirmkr

#include "laapi.h"


#define LIMPASM_MAXPATHSSIZE 256
#define LIMPASM_MAXPATHSIZE (LIMPASM_MAXPATHSSIZE-1)

void LIMPASM_DIRMKR_clear(Lchar* path){
	for(int i=0; i<LIMPASM_MAXPATHSSIZE; i++){
		path[i] = 0;
	}
}

void LIMPASM_DIRMKR_set(Lchar* path_dest, Lchar* path_src){
	for(int i=0; i<LIMPASM_MAXPATHSSIZE; i++){
		path_dest[i] = path_src[i];
		if(path_src[i]==0){
			break;
		}
	}
}

void LIMPASM_DIRMKR_change(Lchar* path_base, Lchar* path_relative){
	Lbool slash = FALSE;
	int i = 0;
	for(; i<LIMPASM_MAXPATHSIZE; i++){
		if(path_base[i]==0){
			break;
		}
		slash = path_base[i]=='/';
	}
	if(!slash){
		path_base[i] = '/';
	}
	else{
		i--;
	}
	for(; i<LIMPASM_MAXPATHSIZE;){
		
		if((*path_relative)=='.'){
			path_relative++;
			
			if((*path_relative)=='.'){
				path_relative++;
				
				if((*path_relative)=='/'){
					path_relative++;
					
					do{
						i--;
						if(path_base[i]=='/'){
							break;
						}
					}while(i>0);
					
					continue;
				}
				
				i++;
				path_base[i] = '.';
				
			}
			else if((*path_relative)=='/'){
				path_relative++;
				continue;
			}
			
			i++;
			path_base[i] = '.';
			
		}
		
		path_relative--;
		do{
			path_relative++;
			i++;
			path_base[i] = *path_relative;
			if((*path_relative)=='/'){
				path_relative++;
				break;
			}
		}while(((*path_relative)!=0)&&(i<LIMPASM_MAXPATHSIZE));
		
		if((*path_relative)==0){
			break;
		}
	}
	
	i++;
	path_base[i] = 0;
	
}


#endif