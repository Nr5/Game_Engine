/*
 * VListLayout.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Nr5
 */

#include "VListLayout.h"

V_List_Layout::V_List_Layout(int Padding,char align,bool scalewidth,bool scaleheight):
padding(padding),align(align),scalewidth(scalewidth),scaleheight(scaleheight){
}
void V_List_Layout::remove(Panel* p,Panel* child){}
void V_List_Layout::add(Panel* p,Panel* child){
	switch (align){
		case H_ALIGN_CENTER:
			child->x=(p->width/2) - (child->width/2);
			break;
		case H_ALIGN_RIGHT:
			child->x=(p->width) - (child->width);
			break;
		default:
			child->x=0;
			break;

	}

	child->y=(p->size()>0)?p->back()->y+p->back()->height+padding:0;
	if(scaleheight)p->height=child->y+child->height;
}
void V_List_Layout::insert(Panel* p,Panel* child,int index){}
void V_List_Layout::resize(Panel* p){}

V_List_Layout::~V_List_Layout() {
	// TODO Auto-generated destructor stub
}

