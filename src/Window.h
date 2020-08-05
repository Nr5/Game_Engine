/*
 * Window.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Nr5
 */

#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL2/SDL.h>
#include "ui/Panel.h"
#include <functional>

class Window : public Panel {
/*
typedef void(*key)(char type,unsigned int key,Window *target);
typedef void(*keydown)(unsigned int key,Window *target);
typedef void(*keyup)(unsigned int key,Window *target);
typedef void(*keyhold)(unsigned int key,Window *target);

typedef void(*ckey)(char type,Window *target);
typedef void(*ckeydown)(Window *target);
typedef void(*ckeyup)(Window *target);
typedef void(*ckeyhold)(Window *target);



typedef void(*mousemotion)(Window *target,int x,int y,int lastx,int lasty);
*/

typedef bool(*windowcloselistener)(Window *target);
	int mx=0;
	int my=0;
	SDL_Renderer* sdl_renderer;
	SDL_GLContext glcontext;
	int window_id;
public:

	windowcloselistener closelistener =0;
	int lastx=0;
	int lasty=0;
	bool keys[65536];
	//Scene *renderer=0;
	SDL_Window *sdlwin=0;
	Window(int x, int y,int width,int height, const char* title,unsigned int sdlflags);
	void winrun();
	bool run();
	virtual ~Window();




};


#endif /* WINDOW_H_ */
