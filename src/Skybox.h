/*
 * Skybox.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Nr5
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "RenderObj.h"
#include  "ShaderProgram.h"
#include "Scene.h"


#include "misc.h"

class Skybox : public RenderObj{
public:
	int layout[1]={3};
	unsigned int indexbuffer[36] = {
		  0, 1, 2,3,
		  3, 2, 6,7,
		  7, 6, 5,4,
		  4, 5, 1,0,
		  0, 3, 7,4,
		  1, 2, 6,5
	};
	float vertexbuffer[24] = {
		-1.0,  1.0,  1.0,
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
	};
	uniform us[1]={{0,0,0,0}};
	unsigned int cubemap_texture;
	virtual void draw();
	Skybox(float* mat,int size,void* xpos,void* ypos,void* zpos,void* xneg,void* yneg,void* zneg);
	Skybox();
	virtual ~Skybox();
};

#endif /* SKYBOX_H_ */
