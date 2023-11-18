#ifndef limpasm_file_h
#define limpasm_file_h

#include <stdio.h>
#include "laapi.h"

#ifndef EOF
	#define EOF 0xffffffff
#endif

#define LIMPASM_FILESMAX 128


typedef enum LAFileType{
	_LAFILE_BUFFER,
	_LAFILE_FILE
}LAFileType;

typedef enum LAFileMode{
	LAFILE_R,
	LAFILE_W,
	LAFILE_A,
	LAFILE_RW
}LAFileMode;

typedef enum LAFileSeek{
	LAFILE_BEG,
	LAFILE_CUR,
	LAFILE_END
}LAFileSeek;


struct _LAFile{
	
	Lbool open;
	LAFileType type;
	LAFileMode mode;
	
	/* Properties for buffer mode */
	
	Luint8* buffer;
	Luint32 buffer_size;
	Luint32 buffer_position;
	
	
	/* Properties for system file mode */
	
	FILE *file;
	
}_LAFiles[LIMPASM_FILESMAX];

typedef Luint32 LAFile;


LAFile LIMPASM_File_openBuffer(Luint8* buffer, Luint32 buffer_size, LAFileMode mode){
	for(int lfi=1; lfi<LIMPASM_FILESMAX; lfi++){
		if(!_LAFiles[lfi].open){
			_LAFiles[lfi].buffer = buffer;
			_LAFiles[lfi].buffer_size = buffer_size;
			_LAFiles[lfi].buffer_position = 0;
			_LAFiles[lfi].type = _LAFILE_BUFFER;
			_LAFiles[lfi].mode = mode;
			_LAFiles[lfi].open = TRUE;
			return lfi;
		}
	}
	return (LAFile)NULL;
}

LAFile LIMPASM_File_openSFile(Lchar* path, LAFileMode mode){
	for(int lfi=1; lfi<LIMPASM_FILESMAX; lfi++){
		if(!_LAFiles[lfi].open){
			_LAFiles[lfi].file = fopen(path,
				mode==LAFILE_R?"r":
				mode==LAFILE_W?"w":
				mode==LAFILE_A?"a":
				mode==LAFILE_RW?"rw":"r");
			if(_LAFiles[lfi].file==NULL){
				return (LAFile)NULL;
			}
			_LAFiles[lfi].type = _LAFILE_FILE;
			_LAFiles[lfi].mode = mode;
			_LAFiles[lfi].open = TRUE;
			return lfi;
		}
	}
	return (LAFile)NULL;
}

void LIMPASM_File_close(LAFile file){
	_LAFiles[file].open = FALSE;
	if(_LAFiles[file].type==_LAFILE_FILE){
		fclose(_LAFiles[file].file);
	}
}

Luint32 LIMPASM_File_getc(LAFile file){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		if(_LAFiles[file].buffer_position>_LAFiles[file].buffer_size){
			if(_LAFiles[file].buffer_position>0x7fffffff){
				return 0;
			}
			return EOF;
		}
		Luint32 chr = _LAFiles[file].buffer[_LAFiles[file].buffer_position];
		_LAFiles[file].buffer_position++;
		return chr;
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		Luint32 chr = fgetc(_LAFiles[file].file);
		return chr;
	}
	return 0;
}

Luint32 LIMPASM_File_ungetc(LAFile file){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		_LAFiles[file].buffer_position--;
		return 0;
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		fseek(_LAFiles[file].file, -1, SEEK_CUR);
		return 0;
	}
	return 0;
}

void LIMPASM_File_putc(LAFile file, Luint32 chr){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		if(_LAFiles[file].buffer_position>_LAFiles[file].buffer_size){
			return;
		}
		_LAFiles[file].buffer[_LAFiles[file].buffer_position] = chr;
		_LAFiles[file].buffer_position++;
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		fputc(chr, _LAFiles[file].file);
	}
}

void LIMPASM_File_read(LAFile file, Luint8* buffer, Luint32 length){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		while(length){
			Luint32 chr = 0;
			if(_LAFiles[file].buffer_position<_LAFiles[file].buffer_size){
				chr = _LAFiles[file].buffer[_LAFiles[file].buffer_position];
			}
			*buffer = chr;
			_LAFiles[file].buffer_position++;
			length--;
			buffer++;
		}
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		fread(buffer, 1, length, _LAFiles[file].file);
	}
}

void LIMPASM_File_write(LAFile file, Luint8* buffer, Luint32 length){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		while(length){
			if(_LAFiles[file].buffer_position<_LAFiles[file].buffer_size){
				_LAFiles[file].buffer[_LAFiles[file].buffer_position] = *buffer;
			}
			_LAFiles[file].buffer_position++;
			length--;
			buffer++;
		}
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		fwrite(buffer, 1, length, _LAFiles[file].file);
	}
}

void LIMPASM_File_seek(LAFile file, LAFileSeek seek, Lsint32 offset){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		switch(seek){
			case LAFILE_BEG:{
				_LAFiles[file].buffer_position = offset;
			}
			break;
			case LAFILE_CUR:{
				_LAFiles[file].buffer_position += offset;
			}
			break;
			case LAFILE_END:{
				_LAFiles[file].buffer_position = _LAFiles[file].buffer_size+offset;
			}
			break;
		}
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		fseek(_LAFiles[file].file, offset,
			seek==LAFILE_BEG?SEEK_SET:
			seek==LAFILE_CUR?SEEK_CUR:
			seek==LAFILE_END?SEEK_END:0);
	}
}

Luint32 LIMPASM_File_tell(LAFile file){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		return _LAFiles[file].buffer_position;
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		return ftell(_LAFiles[file].file);
	}
	return 0;
}

Luint32 LIMPASM_File_(LAFile file){
	if(_LAFiles[file].type==_LAFILE_BUFFER){
		
	}
	else if(_LAFiles[file].type==_LAFILE_FILE){
		
	}
	return 0;
}



#endif