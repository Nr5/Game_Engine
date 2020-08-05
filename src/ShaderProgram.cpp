/*
 * ShaderProgram.cpp
 *
 *  Created on: Jan 29, 2018
 *      Author: Nr5
 */

#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(unsigned int vertexshader,unsigned int geometryshader,unsigned int fragmentshader) {

	id = glCreateProgram();

	glAttachShader(id,vertexshader);
	glAttachShader(id,geometryshader);
	glAttachShader(id,fragmentshader);

	glLinkProgram(id);
	glValidateProgram(id);
/*
	glDeleteShader(vertexshader);
	glDeleteShader(geometryshader);
	glDeleteShader(fragmentshader);
*/

	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length


	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

	for (i = 0; i < count; i++)
	{
	    glGetActiveUniform(id, (GLuint)i, bufSize, &length, &size, &type, name);

	    int u_id=glGetUniformLocation(id,name);
	    uniforms[name]=u_id;
	}


}



ShaderProgram::~ShaderProgram() {
	// TODO Auto-generated destructor stub
}

