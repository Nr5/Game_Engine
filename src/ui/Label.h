/*
 * Label.h
 *
 *  Created on: 29.08.2018
 *      Author: Nr5
 */

#ifndef UI_LABEL_H_
#define UI_LABEL_H_

#include "Panel.h"

#include <SDL2/SDL_ttf.h>

class Label: public Panel {
public:
	TTF_Font *font;
	Label(int x,int y,int width,int height,int bgcolor,TTF_Font *font,const char*  string);
	Label(int x,int y,int bgcolor,TTF_Font *font,const char*  string);
	virtual ~Label();
};
//eventlistener write=[](Panel * panel, SDL_Event event){((Label)panel).str};

#endif /* UI_LABEL_H_ */
