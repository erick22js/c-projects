#ifndef CIVIFOR_VIDEO_DRAWER_H_INCLUDED
#define CIVIFOR_VIDEO_DRAWER_H_INCLUDED

#include "video_opengl.h"


GLuint vertices[] = {
	0, 0,
	0, 1,
	1, 0,
	1, 1,
	
	1, 1,
	1, 2,
	2, 1,
	2, 2,
};

GLuint indices[] = {
	0, 1, 2,
	1, 3, 2,
	
	4, 5, 6,
	5, 7, 6,
};

GLuint vbo;

GLuint ibo;

const GLchar *vertex_src = "\
attribute ivec2 a_pos;\
varying vec2 v_uv;\
void main(){\
	v_uv = a_pos*vec2(1.0, -1.0);\
	gl_Position = vec4(a_pos/2f, 0.0, 1.0);\
}\
";

const GLchar *fragment_src = "\
precision mediump float;\
uniform sampler2D tex;\
varying vec2 v_uv;\
void main(){\
	vec4 color = texture2D(tex, v_uv);\
	gl_FragColor = color;/*vec4(1.0, 0.0, 0.0, 1.0);*/\
}\
";

GLuint apos_location;

GLuint vertexSh;
GLuint fragmentSh;

GLuint program;

unsigned char tex_data[] = {
	0xff, 0x00, 0x00,    0x88, 0x00, 0x00,    0x44, 0x00, 0x00,    0x00, 0x00, 0x00,
	0x88, 0x44, 0x00,    0x66, 0x22, 0x00,    0x22, 0x00, 0x22,    0x00, 0x00, 0x44,
	0x44, 0x88, 0x00,    0x22, 0x66, 0x22,    0x00, 0x22, 0x66,    0x00, 0x00, 0x88,
	0x00, 0xff, 0x00,    0x00, 0x88, 0x44,    0x00, 0x44, 0x88,    0x00, 0x00, 0xff,
};

GLuint texture;

int init(){
	
	int info_status = 0;
	char info_log[1024];
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	vertexSh = ucv4_gl_CreateShader(const_cast<GLchar*>(vertex_src), GL_VERTEX_SHADER);
	
	fragmentSh = ucv4_gl_CreateShader(const_cast<GLchar*>(fragment_src), GL_FRAGMENT_SHADER);
	
	program = ucv4_gl_CreateProgram(vertexSh, fragmentSh);
	
	glUseProgram(program);
	glDeleteShader(vertexSh);
	glDeleteShader(fragmentSh);
	
	apos_location = glGetAttribLocation(program, "a_pos");
	
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	return 0;
}

void update(){
	
	glUseProgram(program);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(apos_location, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLint), (void*)0);
	glEnableVertexAttribArray(apos_location);
	
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);
	
}




#endif // VIDEO_DRAWER_H_INCLUDED
