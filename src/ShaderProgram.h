/*
 * ShaderProgram.h
 *
 *  Created on: Jan 29, 2018
 *      Author: Nr5
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <string>

#include <iostream>
class ShaderProgram {

private:
	std::map<unsigned int,unsigned int> typesizes={
			{5124,  1* sizeof(int)},	//int

			{5126,  1* sizeof(float)},	//float
			{35665, 3* sizeof(float)},	//vec3
			{35666, 4* sizeof(float)}, 	//vec4
			{35676, 4*4* sizeof(float)} //mat4

	};


public:
	void makeUniformBuffer();
	unsigned int id=0;
	std::map<std::string,unsigned int> uniforms;
	char* uniformbuffer=0;
	ShaderProgram(){};
	ShaderProgram(unsigned int vertexshader,unsigned int geometryshader,unsigned int fragmentshader);
	void addUniform(std::string id);
	virtual ~ShaderProgram();
};

#endif /* SHADERPROGRAM_H_ */
