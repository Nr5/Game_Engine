/*
 * RenderObj.cpp
 *
 *  Created on: Jan 30, 2018
 *      Author: Nr5
 */

#include "RenderObj.h"

#include <numeric>

RenderObj::RenderObj(int indexcount,unsigned int* indices,int vertexcount,float* vertices,int attributecount,int* layout,int uniformcount, uniform* uniforms) {
	this->indexcount=indexcount;
	this->indices=indices;

	this->vertexcount=vertexcount;
	this->vertices=vertices;

	this->attributecount=attributecount;
	this->layout=layout;

	this->uniforms=uniforms;
	this->uniformcount=uniformcount;
	glGenBuffers(1,&buffer);


}
void RenderObj::draw(){

	//glMatrixMode(GL_MODELVIEW);
	if (depthtest)	glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);


	bind();
	if(shader)glUseProgram(shader->id);

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

	for (uniform *u= uniforms;u<uniforms+uniformcount;u++){
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


	glDrawElements(drawshape, indexcount, GL_UNSIGNED_INT, indices);

	glDisable(GL_TEXTURE);
	glActiveTexture(0);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	for (RenderObj ro:children)ro.draw();


}
void RenderObj::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, buffer);


	int vertexsize=std::accumulate(layout, layout+attributecount,0);
	glBufferData(GL_ARRAY_BUFFER, vertexcount*vertexsize*sizeof(float), vertices, GL_STATIC_DRAW);

	float* p=0;
	for (int i=0;i< attributecount;i++){
		glVertexAttribPointer(i,layout[i],GL_FLOAT,GL_FALSE,vertexsize*sizeof(float),p);
		p+=layout[i];
		glEnableVertexAttribArray(i);
	}
}

RenderObj::~RenderObj() {
	// TODO Auto-generated destructor stub
}

