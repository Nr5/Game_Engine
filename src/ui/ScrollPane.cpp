/*
 * ScrollPane.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: Nr5
 */

#include "ScrollPane.h"
#include <iostream>
void drawhandle(Panel *p){
	ScrollPane* sp = (ScrollPane*)p->parent;
	//glColor4ubv((unsigned char*) p->colors[p->state*3+1]);
	glColor4ub(0xff,0xff,0xff,0xff);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-.9,.98-sp->scrollpos*2);
	glVertex2f( .9,.98-sp->scrollpos*2);
	glVertex2f( .9,.98- 1.96*(sp->scrollpos+1.f*sp->height/sp->content->height));
	glVertex2f( -.9,.98-1.96*(sp->scrollpos+1.f*sp->height/sp->content->height));
	glEnd();


}
bool scroll(Panel* p,SDL_Event e,int x,int y){
	ScrollPane* sp = (ScrollPane*)p->parent;
	sp->scrollpos=1.f*y/p->height-.5f*sp->height/sp->content->height;
	if(sp->scrollpos<0)sp->scrollpos=0;
	if(sp->scrollpos>1-1.*sp->height/sp->content->height)sp->scrollpos=1-1.*sp->height/sp->content->height;
	sp->content->y=-sp->content->height*sp->scrollpos;
	//p->fgcolor=0x90F0F0F0;

	return true;
}
ScrollPane::ScrollPane():ScrollPane(0,0,100,100,0) {
	// TODO Auto-generated constructor stub

}
ScrollPane::ScrollPane(int x,int y,int width,int height,int bgcolor):
		Panel(x,y,width,height,bgcolor)
{
	
	viewport =new Panel(3,3,width-16,height-6,bgcolor);
	content =new Panel(0,0,width-16,height,bgcolor);
	v_handle =new Panel(width-14,0,14,height,bgcolor);
	//auto scrollistener=scroll;
	//auto draglistener=[](Panel* p,SDL_Event e,int x,int y,int,int){return scroll(p,e,x,y);};
	//auto draglistener2=draglistener;
	//auto draglistener3=draglistener2;
	
	
	v_handle->mouselistener=scroll;
	v_handle->mousedraglistener=[](Panel* p,SDL_Event e,int x,int y,int,int){return scroll(p,e,x,y);};

	v_handle->render=drawhandle;
	Panel::add(v_handle);
	Panel::add(viewport);
	viewport->add(content);



}

void ScrollPane::add(Panel* child){
		content->add(child);
		if (child->y+child->height > content->height){
			content->height=child->y+child->height;
		}
}

ScrollPane::~ScrollPane() {
	// TODO Auto-generated destructor stub
}

