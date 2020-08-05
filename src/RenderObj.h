/*
 * RenderObj.h
 *
 *  Created on: Jan 30, 2018
 *      Author: Nr5
 */

#ifndef RENDEROBJ_H_
#define RENDEROBJ_H_
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include "ShaderProgram.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
enum {
	UNIFORM_FLOAT,	UNIFORM_VEC2,	UNIFORM_VEC3,	UNIFORM_VEC4,
	UNIFORM_DOUBLE,	UNIFORM_DVEC2,	UNIFORM_DVEC3,	UNIFORM_DVEC4,
	UNIFORM_INT,	UNIFORM_IVEC2,	UNIFORM_IVEC3,	UNIFORM_IVEC4,
	UNIFORM_UINT,	UNIFORM_UIVEC2,	UNIFORM_UIVEC3,	UNIFORM_UIVEC4,

	UNIFORM_MAT2,UNIFORM_MAT2x3,UNIFORM_MAT2x4,
	UNIFORM_MAT3,UNIFORM_MAT3x2,UNIFORM_MAT3x4,
	UNIFORM_MAT4,UNIFORM_MAT4x2,UNIFORM_MAT4x3,
};
union types{
	float* f;
	int* i;
	unsigned int* ui;
	double* d;


};
struct uniform{

	int id;
	int type;
	int count;
	types data;
};

class RenderObj {
public:
	bool depthtest=true;

	ShaderProgram *shader=0;
	unsigned int drawshape=GL_TRIANGLES;;

	float* vertices=0;
	int vertexcount=0;

	unsigned int* indices=0;
	int indexcount=0;

	int* layout=0;
	int attributecount=0;

	uniform* uniforms=0;
	int uniformcount=0;

	unsigned int buffer=0;
	unsigned int index_buffer=0;
	std::vector<RenderObj> children;
	float matrix[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	virtual void bind();
	virtual void draw();
	RenderObj(){};
	RenderObj(int indexcount,unsigned int* indices,int vertexcount,float* vertices,int attributecount,int* layout,int uniformcount,uniform* uniforms);
	virtual ~RenderObj();

};

#endif /* RENDEROBJ_H_ */
