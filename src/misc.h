/*
 * misc.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Nr5
 */

#ifndef MISC_H_
#define MISC_H_
#include <string>
#include <fstream>

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

static std::string readfile(const char* filename){
	std::ifstream inFile;
	std::string ret;
	inFile.open(filename);//open the input file
	std::stringstream stream;
	stream << inFile.rdbuf();//read the file
	ret = stream.str();//str holds the content of the file
	inFile.close();

	return ret;
}

static unsigned int compileShader(unsigned int type, const std::string& source){
	unsigned int id= glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id,1,&src,nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS, &result);
	if (!result){
		std::cout <<(type==GL_VERTEX_SHADER?"vertex":type==GL_FRAGMENT_SHADER?"fragment":"geometry")<<"\n";
		int length;
		glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
		char* message= (char*)alloca(length*sizeof(char));
		glGetShaderInfoLog(id,length,&length,message);
		std::cout <<message<<"\n";
		glDeleteShader(id);
		return 0;
	}
	return id;
}



#endif /* MISC_H_ */
