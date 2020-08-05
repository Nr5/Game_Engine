/*
 * geometry.cpp
 *
 *  Created on: 09.07.2018
 *      Author: Nr5
 */
#define PI 3.1415

#include "geometry.h"
RenderObj makeSphere(int lo, int la){
	int vertexcount= lo*la;
	int vertexsize=2;
	int buffersize= vertexcount*vertexsize;
	int indexcount=la*lo*6;
	float *vertices = new float[buffersize];
	unsigned int *indices = new unsigned int[indexcount];



	for (int i=0;i<(vertexcount);i++){
		vertices[i*vertexsize]	= PI*2/lo * (i%lo);
		vertices[i*vertexsize+1]	= PI*2/lo * ((i/lo)+1);
	}


	for (int j=0;j<la-2;j++){
		for (int i=0;i<lo;i++){
			indices[6*lo*j+i*6+0]	=lo*j+(i)+0       +1;
			indices[6*lo*j+i*6+1]	=lo*j+(i)+lo      +1;
			indices[6*lo*j+i*6+2]	=lo*j+(i+1)%lo    +1;

			indices[6*lo*j+i*6+3]	=lo*j+(i+1)%lo    +1;
			indices[6*lo*j+i*6+4]	=lo*j+(i)+lo      +1;
			indices[6*lo*j+i*6+5]	=lo*j+(i+1)%lo+lo +1;
		}
	}

	for (int i=0;i<lo;i++){
		indices[6*(vertexcount-2)+0+i*3]	=0;
		indices[6*(vertexcount-2)+1+i*3]	=i+1;
		indices[6*(vertexcount-2)+2+i*3]	=(i+1)%lo+1;
	}
	for (int i=0;i<lo;i++){
		indices[6*(vertexcount-2)+3*lo+0+i*3]	=(vertexcount-2)+1;
		indices[6*(vertexcount-2)+3*lo+1+i*3]	=(vertexcount-2)-i;
		indices[6*(vertexcount-2)+3*lo+2+i*3]	=(vertexcount-2)-(i+1)%lo;
	}
	int* layout = new int[1]{
		2
	};

	return RenderObj (
		indexcount,		(unsigned int*) indices,
		buffersize,		vertices,
		1,	layout,
		0,	0
	);
}
