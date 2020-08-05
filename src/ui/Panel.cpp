/*
 * Panel.cpp
 *
 *  Created on: 09.08.2018
 *      Author: Nr5
 */

#include "Panel.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
Panel::Panel(int x,int y,int width,int height,int bgcolor):x(x),y(y),width(width),height(height) {

}

void Panel::draw(int absx,int absy,int clipx,int clipy,int clipwidth,int clipheight){

	if(!active)return;

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glLoadIdentity();
	absx+=x;
	absy+=y;
	int cx2=clipx;
	int cy2=clipy;
	if (clipx<absx){
		cx2=absx;
	}
	if (clipy<absy){
		cy2=absy;
	}
	int cw2=(absx+width)-cx2;
	int ch2=(absy+height)-cy2;

	if (cx2+cw2>clipx+clipwidth){
		cw2=clipx+clipwidth-cx2;
	}
	if (cy2+ch2>clipy+clipheight){
			ch2=clipy+clipheight-cy2;
	}
	if(cw2<0||ch2<0)return;
	glViewport(cx2,screenheight-cy2-ch2,cw2,ch2);
	//glTranslatef();
	float zeroclipx=cx2+cw2/2.0;
	float zeroclipy=cy2+ch2/2.0;
	float zeropanelx=absx+width/2.0;
	float zeropanely=absy+height/2.0;
	glTranslatef((2.0/cw2)*(zeropanelx-zeroclipx),-(2.0/ch2)*(zeropanely-zeroclipy),0);

	glScalef((float)width/cw2,(float)height/ch2,1);
		char c;
		for(c =state; !(colors[3*c+0]) && (c+1);c--  );
		if(colors[3*c+0])
			glColor4ubv((const unsigned char*)(colors[3*c+0]));
		else
			glColor4ub(0xff,0,0,0xff);
		
		glBegin(GL_QUADS);
		glVertex2f(-1,-1);
		glVertex2f(1,-1);
		glVertex2f(1,1);
		glVertex2f(-1,1);
		glEnd();


	if (bgimage){
		for(c =state; !(colors[3*c+1]) && (c+1);c--  );
		if(colors[3*c+1])
			glColor4ubv((const unsigned char*)(colors[3*c+1]));
		else
			glColor4ub(0x40,0,0,0x40);
			glEnable(GL_BLEND);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,bgimage);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2f(-1,-1);
			glTexCoord2f(1,1);
			glVertex2f(1,-1);
			glTexCoord2f(1,0);
			glVertex2f(1,1);
			glTexCoord2f(0,0);
			glVertex2f(-1,1);
		glEnd();
		//glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);
		

	}
		glLineWidth(borderwidth);
	
		for(c =state; !(colors[3*c+2]) && (c+1);c--  );
		if(colors[3*c+2])
			glColor4ubv((const unsigned char*)(colors[3*c+2]));
		else
			glColor4ub(0xff,0,0,0xff);
			
		glBegin(GL_LINE_LOOP);
		glVertex2f(-.99,-.99);
		glVertex2f( .99,-.99);
		glVertex2f( .99,.99);
		glVertex2f(-.99,.99);
		glEnd();

	glColor3f(1.f,1.f,1.f);
	if (object) object->draw();
	if (render){
		render(this);

	}

	for (Panel *p:*this)p->draw(absx,absy,cx2,cy2,cw2,ch2);





}

bool Panel::handle_input(SDL_Event event,int absx,int absy,int clipx,int clipy,int clipwidth,int clipheight,int lastx,int lasty){

	if(!active)return false;
	absx+=x;
	absy+=y;

	int cx2=clipx;
	int cy2=clipy;
	if (clipx<absx){
		cx2=absx;
	}
	if (clipy<absy){
		cy2=absy;
	}
	int cw2=(absx+width)-cx2;
	int ch2=(absy+height)-cy2;

	if (cx2+cw2>clipx+clipwidth){
		cw2=clipx+clipwidth-cx2;
	}
	if (cy2+ch2>clipy+clipheight){
			ch2=clipy+clipheight-cy2;
	}
	if (any_of(begin(),end(),[&event,&absx,&absy,&cx2,&cy2,&cw2,&ch2,&lastx,&lasty](Panel* p){
		return 	p->handle_input(event,absx,absy,cx2,cy2,cw2,ch2,lastx,lasty);
	})){
		return true;
	}

	if(keydownlistener && event.type==SDL_KEYDOWN){
		return keydownlistener(this,event);
	}

	if (clicked){
		if(event.type==SDL_MOUSEBUTTONUP){
			clicked=false;
			if ((event.motion.x > cx2 && event.motion.x < cx2+cw2 &&
					 event.motion.y > cy2 && event.motion.y < cy2+ch2)){
				state=HOVER;

			}
			else{
				state=STANDARD;
			}
			return true;
		}
		if(mousedraglistener && event.type==SDL_MOUSEMOTION){
			return mousedraglistener(this,event,event.motion.x - absx,event.motion.y-absy,lastx - absx,(event.motion.y)-absy);

		}


	}

	if (event.type==SDL_MOUSEMOTION  &&
			!(event.motion.x > cx2 &&
			event.motion.x < cx2+cw2 &&

			event.motion.y > cy2 &&
			event.motion.y < cy2+ch2)&&

			lastx > cx2 &&
			lastx < cx2+cw2 &&

			lasty > cy2 &&
			lasty < cy2+ch2&&
			!(clicked && mousedraglistener && *mousedraglistener)
			){
		state=STANDARD;
		if(mousexitlistener){
			return mousexitlistener(this,event,event.motion.x - absx,event.motion.y-absy);

		}
	}

	if ((event.motion.x > cx2 && event.motion.x < cx2+cw2 &&
		 event.motion.y > cy2 && event.motion.y < cy2+ch2)){

		if (event.type==SDL_MOUSEBUTTONDOWN){
			clicked=true;
			state=CLICKED;
			if(mouselistener){
				return mouselistener(this,event,event.motion.x - absx,event.motion.y - absy);

			}
		}





		if(mousemotionlistener &&event.type==SDL_MOUSEMOTION  && !clicked){
			return mousemotionlistener(this,event,event.motion.x - absx,event.motion.y-absy,lastx - absx,(event.motion.y)-absy);

		}

		if (event.type==SDL_MOUSEMOTION  &&
				!(lastx > cx2 &&
				lastx < cx2+cw2 &&

				lasty > cy2 &&
				lasty < cy2+ch2)
				){
					
			state=HOVER;
			if (mouseenterlistener){
				return mouseenterlistener(this,event,event.motion.x - absx,event.motion.y-absy);

			}
		}

	}

	return false;




}
bool Panel::run(){
	if(!active) return true;
	if (update && *update) (*update)(this);
	for (Panel *p:*this){
		if (!p->run()){
			return false;
		}

	}

	return running;
}
void Panel::add(Panel* child){
	child->parent=this;
	if(layout)layout->add(this,child);
	push_back(child);
}
Panel::~Panel() {
	for (Panel* child : *this){
		delete child;
	}
}

