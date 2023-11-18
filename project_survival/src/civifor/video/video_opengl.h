#ifndef CIVIFOR_VIDEO_OPENGL_H_INCLUDED
#define CIVIFOR_VIDEO_OPENGL_H_INCLUDED

#include <stdio.h>

//#include <SDL2/SDL.h>
//#include <GL/glew.h>
//#include <SDL2/SDL_opengl.h>

#include "../util/util_type.h"

SDL_Window *ucv4_opengl_window = nullptr;
SDL_GLContext ucv4_opengl_ctx = nullptr;

int ucv4_opengl_width = 0;
int ucv4_opengl_height = 0;

bool ucv4_opengl_started = false;


/**
	WINDOW AND OPENGL CONTEXT INITIALIZING
*/

bool ucv4_opengl_Init(char* window_name, unsigned int window_width, unsigned int window_height){
	if(ucv4_opengl_started){
		return false;
	}
	
	SDL_Init(SDL_INIT_VIDEO);
	
	ucv4_opengl_window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	if (ucv4_opengl_window==nullptr){
		return false;
	}
	
	ucv4_opengl_ctx = SDL_GL_CreateContext(ucv4_opengl_window);
	if (ucv4_opengl_ctx==nullptr){
		return false;
	}
	
	Uint32 init_status = glewInit();
	if (init_status){
		return false;
	}
	
	ucv4_opengl_started = true;
	
	return true;
}

void ucv4_opengl_Update(){
	SDL_GL_SwapWindow(ucv4_opengl_window);
	SDL_GetWindowSize(ucv4_opengl_window, &ucv4_opengl_width, &ucv4_opengl_height);
	glViewport(0, 0, ucv4_opengl_width, ucv4_opengl_height);
}

bool ucv4_opengl_End(){
	if (!ucv4_opengl_started){
		return false;
	}
	
	SDL_GL_DeleteContext(ucv4_opengl_ctx);
	SDL_DestroyWindow(ucv4_opengl_window);
	
	return true;
}


/**
	OPENGL LIGHTWEIGHT FUNCTIONS
*/

GLint ucv4_gl_CreateShader(char* src_shader, GLenum type){
	/// Shader compilaion info and status
	GLint info_status = 0;
	GLchar info_log[1024];
	
	/// Generate shader and retrieves his id
	GLint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &src_shader, NULL);
	glCompileShader(shader_id);
	
	/// Retrieves the shader info
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &info_status);
	if (info_status==0){
		glGetShaderInfoLog(shader_id, sizeof(info_log)-1, NULL, info_log);
		printf("Error in %s Shader:\n\"%s\"\n", (type==GL_VERTEX_SHADER?"Vertex":type==GL_FRAGMENT_SHADER?"Fragment":"Unknow"),info_log);
		return 0;
	}
	return shader_id;
}

GLint ucv4_gl_CreateProgram(GLint shader_vertex, GLint shader_fragment){
	/// Program compilaion info and status
	GLint info_status = 0;
	GLchar info_log[1024];
	
	/// Generate program and retrieves his id
	GLint program_id = glCreateProgram();
	glAttachShader(program_id, shader_vertex);
	glAttachShader(program_id, shader_fragment);
	glLinkProgram(program_id);
	
	/// Retrieves the program info
	glGetProgramiv(program_id, GL_LINK_STATUS, &info_status);
	if (info_status==0){
		glGetProgramInfoLog(program_id, sizeof(info_log)-1, NULL, info_log);
		printf("Error in Program:\n\"%s\"\n", info_log);
		return 0;
	}
	return program_id;
}



#endif // CIVIFOR_VIDEO_OPENGL_H_INCLUDED
