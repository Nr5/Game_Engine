/*
 * Label.cpp
 *
 *  Created on: 29.08.2018
 *      Author: Nr5
 */

#include "Label.h"
#include <iostream>

Label::Label(int x,int y,int bgcolor,TTF_Font* font,const char* string):Panel(),font(font){
		if (font){
		this->x =x;
		this->y=y;
		SDL_Surface* surface = TTF_RenderText_Blended(font, string,SDL_Color {255,255,255}); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    	
    	
    	unsigned int texture_format;
    	unsigned int colors = surface->format->BytesPerPixel;
		if (colors == 4) {   // alpha
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA_EXT;
		} else {             // no alpha
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR_EXT;	
		}

		glGenTextures(1, &bgimage);
		glBindTexture(GL_TEXTURE_2D, bgimage);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0,	GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       	
       	width=surface->w;
		height=surface->h;
       	
       	SDL_FreeSurface(surface);
		glBindTexture(GL_TEXTURE_2D, 0);

       	
       	
       	
	}else {
		std::cout << "missing font\n";
	} 
}

Label::Label(int x,int y,int width,int height,int bgcolor,TTF_Font* font,const char* string):
	Label(x,y,bgcolor,font,string){
	this->width=width;
	this->height=height;
	
}

Label::~Label() {
	// TODO Auto-generated destructor stub
}

