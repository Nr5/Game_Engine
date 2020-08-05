/*
 * Renderer.h
 *
 *  Created on: Jan 29, 2018
 *      Author: Nr5
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "ShaderProgram.h"
#include <numeric>
#include "RenderObj.h"
#include <algorithm>
#include <fstream>
#include "RenderObj.h"
/*
enum {
	UNIFORM_FLOAT,	UNIFORM_VEC2,	UNIFORM_VEC3,	UNIFORM_VEC4,
	UNIFORM_DOUBLE,	UNIFORM_DVEC2,	UNIFORM_DVEC3,	UNIFORM_DVEC4,
	UNIFORM_INT,	UNIFORM_IVEC2,	UNIFORM_IVEC3,	UNIFORM_IVEC4,
	UNIFORM_UINT,	UNIFORM_UIVEC2,	UNIFORM_UIVEC3,	UNIFORM_UIVEC4,

	UNIFORM_MAT2,UNIFORM_MAT2x3,UNIFORM_MAT2x4,
	UNIFORM_MAT3,UNIFORM_MAT3x2,UNIFORM_MAT3x4,
	UNIFORM_MAT4,UNIFORM_MAT4x2,UNIFORM_MAT4x3,
};
*/
class Renderer {
	void drawObj(RenderObj object);

public:
	RenderObj object;
	ShaderProgram shader;
	unsigned int drawshape=GL_TRIANGLES;;
	virtual void draw();
	virtual ~Renderer();
};

#endif /* RENDERER_H_ */
