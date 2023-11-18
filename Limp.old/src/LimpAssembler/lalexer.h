#ifndef limpasm_lexer_h
#define limpasm_lexer_h

#include "lafile.h"
#include "ladirmkr.h"

#define LIMPASM_MAXLEXERS LIMPASM_FILESMAX


typedef struct LACaret{
	Luint32 index; /* Position inside file */
	Luint32 line; /* Line actual index */
	Luint32 offset; /* Offset in current line */
}LACaret;

struct LALexer{
	
	Lbool open;
	LAFile file;
	
	Lchar path[LIMPASM_MAXPATHSSIZE];
	
	LACaret caret;
	
	Luint32 buffer;
	Lbool buffer_inuse;
	
}_LALexers[LIMPASM_MAXLEXERS];

typedef struct LALexer LALexer;


LALexer *LIMPASM_Lexer_openSFile(Lchar* path){
	for(Luint32 lli=1; lli<LIMPASM_MAXLEXERS; lli++){
		if(!_LALexers[lli].open){
			LAFile file = LIMPASM_File_openSFile(path, LAFILE_R);
			if(file==(LAFile)NULL){
				return NULL;
			}
			LIMPASM_DIRMKR_set(_LALexers[lli].path, path);
			_LALexers[lli].file = file;
			_LALexers[lli].open = TRUE;
			_LALexers[lli].caret.index = 0;
			_LALexers[lli].caret.line = 1;
			_LALexers[lli].caret.offset = 1;
			return &_LALexers[lli];
		}
	}
	return NULL;
}

LALexer *LIMPASM_Lexer_openBuffer(Luint8* buffer, Luint32 length){
	for(Luint32 lli=1; lli<LIMPASM_MAXLEXERS; lli++){
		if(!_LALexers[lli].open){
			LAFile file = LIMPASM_File_openBuffer(buffer, length, LAFILE_R);
			if(file==(LAFile)NULL){
				continue;
			}
			LIMPASM_DIRMKR_set(_LALexers[lli].path, "Buffer");
			_LALexers[lli].file = file;
			_LALexers[lli].open = TRUE;
			_LALexers[lli].caret.index = 0;
			_LALexers[lli].caret.line = 1;
			_LALexers[lli].caret.offset = 1;
			return &_LALexers[lli];
		}
	}
	return NULL;
}

void LIMPASM_Lexer_close(LALexer *lexer){
	LIMPASM_File_close(lexer->file);
	lexer->open = FALSE;
}

Luint32 _LIMPASM_Lexer_get(LALexer *lexer){
	Luint32 chr;
	if(lexer->buffer_inuse){
		lexer->buffer_inuse = FALSE;
		lexer->buffer;
	}
	else{
		chr = LIMPASM_File_getc(lexer->file);
	}
	if(chr=='\n'){
		lexer->caret.line++;
		lexer->caret.offset = 0;
	}
	lexer->caret.offset++;
	lexer->caret.index++;
	
	if(chr==0){
		return EOF;
	}
	return chr;
}

Luint32 LIMPASM_Lexer_get(LALexer *lexer){
	Luint32 chr = _LIMPASM_Lexer_get(lexer);
	lexer->buffer = chr;
	if(chr=='\\'){
		chr = _LIMPASM_Lexer_get(lexer);
		
		if(chr=='\n'){
			chr = ' ';
		}
		else{
			lexer->buffer_inuse = TRUE;
		}
	}
	return chr;
}

Luint32 _LIMPASM_Lexer_unget(LALexer *lexer){
	Luint32 chr;
	if(lexer->buffer_inuse){
		lexer->buffer_inuse = FALSE;
		LIMPASM_File_ungetc(lexer->file);
		LIMPASM_File_ungetc(lexer->file);
		chr = LIMPASM_File_getc(lexer->file);
		LIMPASM_File_ungetc(lexer->file);
	}
	else{
		LIMPASM_File_ungetc(lexer->file);
		chr = LIMPASM_File_getc(lexer->file);
		LIMPASM_File_ungetc(lexer->file);
	}
	if(chr=='\n'){
		lexer->caret.line--;
		lexer->caret.offset = 0xffff;
	}
	lexer->caret.offset--;
	lexer->caret.index--;
	
	if(chr==0){
		return EOF;
	}
	return chr;
}

Luint32 LIMPASM_Lexer_unget(LALexer *lexer){
	Luint32 chr = _LIMPASM_Lexer_unget(lexer);
	
	if(chr=='\n'){
		Luint32 chr = _LIMPASM_Lexer_unget(lexer);
		
		if(chr=='\\'){
			
		}
		else{
			_LIMPASM_Lexer_get(lexer);
			chr = ' ';
		}
	}
	
	return chr;
}





#endif