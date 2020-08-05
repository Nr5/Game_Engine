/*
 * Skybox.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: Nr5
 */

#include "Skybox.h"

Skybox::Skybox(float* mat,int size,void* xpos,void* ypos,void* zpos,void* xneg,void* yneg,void* zneg):
		RenderObj(		36,	indexbuffer,
						8,	vertexbuffer,
						1,	layout,
						1,	us
		){
	shader=new ShaderProgram(
		compileShader(GL_VERTEX_SHADER,readfile("./shaders/skybox.vs")),
		0,//compileShader(GL_GEOMETRY_SHADER,readfile("basic.gs")),
		compileShader(GL_FRAGMENT_SHADER,readfile("./shaders/skybox.fs"))
		);
	uniforms[0] =uniform{glGetUniformLocation(shader->id,"u_Matrix"),	UNIFORM_MAT4,1,mat};

	// TODO Auto-generated constructor stub
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glGenTextures(1, &cubemap_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, xpos);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, xneg);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, ypos);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, yneg);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, zpos);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, zneg);
		std::cout<<"tex_init\n";

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);




	depthtest=true;
	std::cout<<"c\n";
	drawshape=GL_QUADS;
}
void  Skybox::draw(){

	glEnable(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
	RenderObj::draw();

/*
	glDisable(GL_TEXTURE);
	glActiveTexture(0);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
*/
	//for (RenderObj ro:children)ro.draw();

}
Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}
Skybox::Skybox() {
	// TODO Auto-generated destructor stub
}
