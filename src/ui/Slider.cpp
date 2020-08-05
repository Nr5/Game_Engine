/*
 * Slider.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: Nr5
 */

#include "Slider.h"
#include <iostream>
#include <type_traits>
//#include <math.h>

template <class T>
bool Slider<T>::slidermouselistener(Panel *p,SDL_Event event,int x,int y){
	Slider<T> *slider=((Slider<T>*)p);
	//x=x-p->width*.025;
	int swidth  = p->width;
	if (x>=swidth){
		*(slider->value) =slider->max;
		return true;
	} else if (x<=0){
		*(slider->value) =slider->min;
		return true;
	}
	
	*slider->value=1.f*(slider->max-slider->min)*x/swidth  +slider->min;
	
	return true;
};
template <class T>
bool Slider<T>::slidermousedraglistener(Panel *p,SDL_Event event,int x,int y,int,int){
	return slidermouselistener(p,event,x,y);
};

template <class T>
void Slider<T>::sliderrender(Panel* p)	{
	Slider<T> *slider =(Slider<T>*)p;
	glTranslatef(-1.f,0,0);
	glScalef(2.f/(slider->max),1,1);
	
	float q=1.f*(*slider->value-slider->min)/(slider->max-slider->min);
	unsigned char* color=(unsigned char*)(slider->colors[p->state*3+1]);
	glColor4ubv(color);
	
	glBegin(GL_QUADS);
	glVertex2f( *(slider->value) , -.8);
	glVertex2f( *(slider->value) ,  .8);
	glVertex2f( 0,  .8);
	glVertex2f( 0, -.8);
	glEnd();

	if(std::is_floating_point<T>::value || (slider->max-slider->min) > 32){
			return;
	}
	
	glLineWidth(1);
	
	
	glColor4ub(0,0,0,0xff);
	glBegin(GL_LINES);
	

	for (int i =slider->min;i<slider->max;i++){
		glVertex2f(i,-.95);
		glVertex2f(i,.95);
	}
	glEnd();


	glScalef((slider->max)/2.f,1,1);
	glTranslatef(1.f,0,0);
	char c;
	for(c =p->state; !(p->colors[3*c+2]) && (c+1);c--  );
	if(p->colors[3*c+2])
		glColor4ubv((const unsigned char*)(p->colors[3*c+2]));
	else
		glColor4ub(0xff,0,0,0xff);
			
	glBegin(GL_LINE_LOOP);
	glVertex2f(-.99,-1);
	glVertex2f( 1,-1);
	glVertex2f( 1,1);
	glVertex2f(-.99,1);
	glEnd();
};

template <>
void Slider<float>::getlimits(){
	min=0.f;
	max=1.f;
}
template <class T>
void Slider<T>::getlimits(){
	min=std::numeric_limits<T>::min();
	max=std::numeric_limits<T>::max();
}

template <class T>
Slider<T>::Slider(int x,int y,int width,int height,int bgcolor):
	Panel(x,y,width,height,bgcolor){

	getlimits();

	mouselistener=Slider<T>::slidermouselistener;
	mousedraglistener=Slider<T>::slidermousedraglistener;
	
	render=Slider<T>::sliderrender;


}
template <class T>
Slider<T>::Slider(): Slider(0,0,100,20,0){};
template <class T>
Slider<T>::~Slider() {
	// TODO Auto-generated destructor stub
}
template <class T>
void Slider<T>::setValue(T* value){
	this->value=value;
	//handle->x=(*value-min)/(max-min)*(width-10);
}
template <class T>
void Slider<T>::setValue(T value){
	*(this->value)=value;
	//handle->x=(value-min)/(max-min)*(width-10);
}

template class Slider<char>;
template class Slider<unsigned char>;

template class Slider<int>;
template class Slider<unsigned int>;

template class Slider<long>;
template class Slider<unsigned long>;

template class Slider<float>;
template class Slider<double>;


