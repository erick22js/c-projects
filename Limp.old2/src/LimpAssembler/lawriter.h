#ifndef limpasm_writer_h
#define limpasm_writer_h

#include "lafile.h"


typedef struct LAWriter{
	
	LAFile file;
	
}LAWriter;


void LIMPASM_Writer_open(LAWriter *writer, Lchar* path){
	if(path=="#DEBUG"){
		writer->file = LIMPASM_File_openBuffer(_LIMPBus_g_ram, sizeof(_LIMPBus_g_ram), LAFILE_W);
	}
	else{
		writer->file = LIMPASM_File_openSFile(path, LAFILE_W);
	}
}

void LIMPASM_Writer_close(LAWriter *writer){
	LIMPASM_File_close(writer->file);
}

void LIMPASM_Writer_put8(LAWriter *writer, Luint8 data){
	LIMPASM_File_putc(writer->file, data);
}

void LIMPASM_Writer_put16(LAWriter *writer, Luint16 data){
	LIMPASM_File_putc(writer->file, (Luint8)(data));
	LIMPASM_File_putc(writer->file, (Luint8)(data>>8));
}

void LIMPASM_Writer_put32(LAWriter *writer, Luint32 data){
	LIMPASM_File_putc(writer->file, (Luint8)(data));
	LIMPASM_File_putc(writer->file, (Luint8)(data>>8));
	LIMPASM_File_putc(writer->file, (Luint8)(data>>16));
	LIMPASM_File_putc(writer->file, (Luint8)(data>>24));
}

void LIMPASM_Writer_putBuffer(LAWriter *writer, Luint8* buffer, Luint32 length){
	LIMPASM_File_write(writer->file, buffer, length);
}

void LIMPASM_Writer_setPosition(LAWriter *writer, Luint32 offset){
	LIMPASM_File_seek(writer->file, LAFILE_BEG, offset);
}

void LIMPASM_Writer_movePosition(LAWriter *writer, Lsint32 offset){
	LIMPASM_File_seek(writer->file, LAFILE_CUR, offset);
}

Luint32 LIMPASM_Writer_getPosition(LAWriter *writer){
	return LIMPASM_File_tell(writer->file);
}



#endif