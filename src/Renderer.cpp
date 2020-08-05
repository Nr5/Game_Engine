/*
 * Renderer.cpp
 *
 *  Created on: Jan 29, 2018
 *      Author: Nr5
 */

#include "Renderer.h"

//#include "misc.h"
#include <iostream>
void Renderer::drawObj(RenderObj ro){

	//glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE);
	for (RenderObj o : ro.children){
		drawObj(o);
	}
	glUseProgram(shader.id);

	ro.bind();

	typedef void(*uniformfunc)(int id,int count,const float* data);
	typedef void(*uniformintfunc)(int id,int count,const int* data);
	typedef void(*uniformuintfunc)(int id,int count,const unsigned int* data);
	typedef void(*uniformdoublefunc)(int id,int count,const double* data);

	typedef void(*uniformmatfunc)(int id,int count,unsigned char,const float *data);

	uniformfunc uniformfunctions[4]={
			glUniform1fv,glUniform2fv,glUniform3fv,glUniform4fv,
	};
	uniformdoublefunc uniformdoublefunctions[4]={
				glUniform1dv,glUniform2dv,glUniform3dv,glUniform4dv,
	};

	uniformintfunc uniformintfunctions[4]={
				glUniform1iv,glUniform2iv,glUniform3iv,glUniform4iv,
	};
	uniformuintfunc uniformuintfunctions[4]={
				glUniform1uiv,glUniform2uiv,glUniform3uiv,glUniform4uiv,
	};



	uniformmatfunc uniformmatfunctions[9]={
			glUniformMatrix2fv,glUniformMatrix2x3fv,glUniformMatrix2x4fv,
			glUniformMatrix3fv,glUniformMatrix3x2fv,glUniformMatrix3x4fv,
			glUniformMatrix4fv,glUniformMatrix4x2fv,glUniformMatrix4x3fv
	};

	for (uniform *u= ro.uniforms;u<ro.uniforms+ro.uniformcount;u++){
		if (u->type<4){
			uniformfunctions[u->type](u->id,u->count,u->data.f);
		}else if (u->type<8){
			uniformdoublefunctions[u->type-4](u->id,u->count,u->data.d);
		}else if (u->type<12){
			uniformintfunctions[u->type-8](u->id,u->count,u->data.i);
		}else if (u->type<16){
			uniformuintfunctions[u->type-12](u->id,u->count,u->data.ui);
		}else{
			uniformmatfunctions[u->type-16](u->id,u->count,GL_FALSE,u->data.f);
		}
	}


	glDrawElements(drawshape, ro.indexcount, GL_UNSIGNED_INT, ro.indices);






}

void Renderer::draw() {

	//glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	drawObj(object);
}

Renderer::~Renderer() {

}

