/*
 * Checkbox.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: Nr5
 */

#include "Checkbox.h"


Checkbox::Checkbox(int x,int y,int size): Panel(x,y,size,size,0) {
	// TODO Auto-generated constructor stub
	render=[](Panel *p){
		Checkbox* cb= (Checkbox*) p;
		
		glBegin(GL_LINE_LOOP);
		glVertex2f(-.99f,-.99f);
		glVertex2f(.99f,-.99f);
		glVertex2f(.99f,.99f);
		glVertex2f(-.99f,.99f);
		glEnd();
		
		if (!cb->state) return;
		if (! (  (*(cb->state)) & cb->bitflag ) )return;
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1,1,1);
		glVertex2f(0.3f,.2f);
		glColor3f(.6,.6,.6);
		glVertex2f(-.8f,-.8f);
		glVertex2f(.8f,-.8f);
		glVertex2f(.8f,.8f);
		glVertex2f(-.8f,.8f);
		glVertex2f(-.8f,-.8f);
		glEnd();
	};
	
	checkboxclicked=[](Panel* p,SDL_Event,int,int){
		Checkbox* cb= (Checkbox*) p;
		
		if (!cb->state) return true;
		
		if (*(cb->state) & cb->bitflag) {
			*(cb->state) &= ~(cb->bitflag);
		} else {
			*(cb->state) |= cb->bitflag;
		}
		
		return true;
	};
	
	mouselistener=checkboxclicked;
}
Checkbox::Checkbox(): Checkbox(0,0,20) {
	// TODO Auto-generated constructor stub

}
Checkbox::~Checkbox() {
	// TODO Auto-generated destructor stub
}

