/*
 * Panel.h
 *
 *  Created on: 09.08.2018
 *      Author: Nr5
 */

#ifndef UI_PANEL_H_
#define UI_PANEL_H_
#include <list>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "./AbstractLayout.h"
#include "../RenderObj.h"

typedef bool(*eventlistener)(Panel *target,SDL_Event event);
typedef bool(*mouseeventlistener)(Panel *target,SDL_Event event,int x,int y);
typedef bool(*mousemotioneventlistener)(Panel *target,SDL_Event event,int x,int y,int lastx,int lasty);
typedef void(*updatefunc)(Panel *target);
	
class Panel: public std::list<Panel*> {
private:
	bool clicked=false;

protected:
public:
	static int screenwidth;
	static int screenheight;

	
enum drawstate{
	STANDARD=0,
	HOVER=1,
	CLICKED=2,
	SELECTED=3
};
	void* data;
	bool active=true;
	Panel* parent=0;
	float borderwidth=1;
	eventlistener keydownlistener=0;
	mouseeventlistener mouselistener=0;
	mouseeventlistener mouseenterlistener=0;
	mouseeventlistener mousexitlistener=0;
	mousemotioneventlistener mousemotionlistener=0;
	mousemotioneventlistener mousedraglistener=0;
	updatefunc update=0;
	void(*render)(Panel *panel)=0;


	drawstate state=STANDARD;
	unsigned int* colors[12]; 
	
	RenderObj* object=0;
	bool running=true;
	unsigned int bgimage=0;
	int bordercolor=0;
	int x,y,width,height;
	AbstractLayout* layout=0;
	Panel():Panel(0,0,0,0,0){};
	Panel(int x,int y,int width,int height,int bgcolor);
	virtual ~Panel();
	virtual void draw(int,int,int,int,int,int);
	virtual bool handle_input(SDL_Event event,int,int,int,int,int,int,int,int);
	virtual bool run();
	virtual void add(Panel* child);
};




#endif /* UI_PANEL_H_ */
