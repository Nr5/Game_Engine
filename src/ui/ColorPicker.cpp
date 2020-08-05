#include "ColorPicker.h"
#include <math.h>
#include <iostream>
#include <limits>

template <class Q>
Q limit(Q x){return std::numeric_limits<Q>::max();}
template <class Q=float>
float limit(float f){return 1.f;}
template <class Q=double>
double limit(double d){return 1.;}

void selectColor(float* c){glColor3fv(c);};
void selectColor(double* c){glColor4dv(c);};
void selectColor(const signed char* c){ glColor4bv(c);};
void selectColor(unsigned char* c){glColor4ubv(c);};
void selectColor(int* c){glColor4iv(c);};
void selectColor(unsigned int* c){glColor4uiv(c);};
void selectColor(short* c){glColor4sv(c);};
void selectColor(unsigned short* c){glColor4usv(c);};








template <class T>
bool pickColor(Panel *p,SDL_Event event,int x,int y){
	y=p->height-y;
	T* value=((ColorPicker<T>* )p->parent)->value;
	T* color=((ColorPicker<T>* )p->parent)->color;

	x=x-p->width/2;
	y=y-p->height/2;

	float d=sqrt(x*x+y*y)/(p->width/2);
	if (d<0)d=0;

	if(d>1)d=1;
	float angle = atan((float)y/x)+M_PI*(x<0);
	if (angle<0)angle+=M_PI*2;

	float r=1.f-(angle<M_PI? angle*2.4/(M_PI*2) :abs(2*M_PI -angle)*2.4/(M_PI*2) );
	float g=1.f-abs(M_PI*2/3   -angle)*2.4/(M_PI*2) ;
	float b=1.f-abs(M_PI*2*2/3 -angle)*2.4/(M_PI*2) ;
	if(r<0)r=0;
	if(g<0)g=0;
	if(b<0)b=0;

	value[0]=limit<T>(value[0])*(1-d)+limit<T>(value[0])*d*r;
	value[1]=limit<T>(value[1])*(1-d)+limit<T>(value[1])*d*g;
	value[2]=limit<T>(value[2])*(1-d)+limit<T>(value[2])*d*b;
	value[3]=1;

	color[0]=value[0]*((ColorPicker<T>*)p->parent)->brightness;
	color[1]=value[1]*((ColorPicker<T>*)p->parent)->brightness;
	color[2]=value[2]*((ColorPicker<T>*)p->parent)->brightness;
	//color[3]=((ColorPicker<T>*)p->parent)->opacity;

	//((ColorPicker<T>*)p->parent)->preview.bgcolor=*((unsigned int*)((ColorPicker<T>*)p->parent)->color);

}
template <class T>
bool pickBrightness(Panel *p,SDL_Event event,int x,int y){
	y=p->height-y;
	((ColorPicker<T>*)p->parent)->brightness=1.f*y/p->height;
	if ( ((ColorPicker<T>*)p->parent)->brightness > 1)((ColorPicker<T>*)p->parent)->brightness=1;
	std::cout << ((ColorPicker<T>*)p->parent)->brightness << "\n";


	((ColorPicker<T>*)p->parent)->color[0]=((ColorPicker<T>*)p->parent)->value[0]*((ColorPicker<T>*)p->parent)->brightness;
	((ColorPicker<T>*)p->parent)->color[1]=((ColorPicker<T>*)p->parent)->value[1]*((ColorPicker<T>*)p->parent)->brightness;
	((ColorPicker<T>*)p->parent)->color[2]=((ColorPicker<T>*)p->parent)->value[2]*((ColorPicker<T>*)p->parent)->brightness;
	//((ColorPicker<T>*)p->parent)->color[3]=((ColorPicker<T>*)p->parent)->opacity;
	return 1;
}
template <class T>
bool pickOpacity(Panel *p,SDL_Event event,int x,int y){
	y=p->height-y;
	((ColorPicker<T>*)p->parent)->opacity=1.f*y/p->height;

	((ColorPicker<T>*)p->parent)->color[0]=((ColorPicker<T>*)p->parent)->value[0]*((ColorPicker<T>*)p->parent)->brightness;
	((ColorPicker<T>*)p->parent)->color[1]=((ColorPicker<T>*)p->parent)->value[1]*((ColorPicker<T>*)p->parent)->brightness;
	((ColorPicker<T>*)p->parent)->color[2]=((ColorPicker<T>*)p->parent)->value[2]*((ColorPicker<T>*)p->parent)->brightness;
	//((ColorPicker<T>*)p->parent)->color[3]=((ColorPicker<T>*)p->parent)->opacity;
	return 1;

}
template <class T>
void drawBall(Panel* p){
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(((ColorPicker<T>*)p->parent)->brightness,((ColorPicker<T>*)p->parent)->brightness,((ColorPicker<T>*)p->parent)->brightness);
	glVertex2f(0,0);
	for (float angle=0;angle<2*M_PI;angle+=.01){
		float r=1.f-(angle<M_PI? angle*2/(M_PI*2) :abs(2*M_PI -angle)*2/(M_PI*2) );
		float g=1.f-abs(M_PI*2/3   -angle)*2/(M_PI*2) ;
		float b=1.f-abs(M_PI*2*2/3 -angle)*2/(M_PI*2) ;

		if(r<0)r=0;
		if(g<0)g=0;
		if(b<0)b=0;



		glColor3f( ((ColorPicker<T>*)p->parent)->brightness*r,((ColorPicker<T>*)p->parent)->brightness*g,((ColorPicker<T>*)p->parent)->brightness*b );
		glVertex2f(cos(angle),sin(angle));
	}
	glEnd();
	glColor3f(1.f,1.f,1.f);
}
template <class T>
void drawBrightness(Panel *p){
	glBegin(GL_QUADS);
	glColor3ub(0,0,0);
	glVertex2f(-1.f,-1.f);
	glVertex2f(1.f,-1.f);
	selectColor( ((ColorPicker<T>* )p->parent)->value);
	glVertex2f(1.f,1.f);
	glVertex2f(-1.f,1.f);
	glEnd();
	glColor4f(1.,1.,1.,1.);
	glBegin(GL_LINES);
	glVertex2f(-1.f,((ColorPicker<T>*)p->parent)->brightness*2-1);
	glVertex2f(1.f,((ColorPicker<T>*)p->parent)->brightness*2-1);
	glEnd();
}
void drawOpacity(Panel *p){
	//((ColorPicker*)p->parent)->opacity=y/p->height;
}
template <class T>
void drawPreview(Panel *p){
	selectColor(((ColorPicker<T>*)p->parent)->color);
	glBegin(GL_QUADS);
	glVertex2f(-1,-1);
	glVertex2f(1,-1);
	glVertex2f(1,1);
	glVertex2f(-1,1);
	glEnd();

}

template <class T>
ColorPicker<T>::ColorPicker(int x,int y,int width,int height,int bgcolor):
		Panel(x,y,width,height,bgcolor)
	{
	colorBall =new Panel(0,0,height,height,0) ;
	brightnessPicker =new Panel(height,width-height,(width-height)/2,height+height-width,0) ;
	opacityPicker =new Panel(height+(width-height)/2,width-height,(width-height)/2,height+height-width,0);
	preview =new Panel(height,0,width-height,width-height,0);

	colorBall->mouselistener=pickColor<T>;
	colorBall->mousedraglistener=[](Panel* p,SDL_Event event,int x,int y,int lastx,int lasty){
			pickColor<T>(p,event,x,y);
			return true;
	};
	brightnessPicker->mouselistener=pickBrightness<T>;
	brightnessPicker->mousedraglistener=[](Panel* p,SDL_Event event,int x,int y,int lastx,int lasty){
		pickBrightness<T>(p,event,x,y);
		return true;
	};

	colorBall->render=drawBall<T>;
	brightnessPicker->render=drawBrightness<T>;
	preview->render=drawPreview<T>;
	add(colorBall);
	add(brightnessPicker);
	add(opacityPicker);
	add(preview);

}

template <class T>
ColorPicker<T>::ColorPicker(): ColorPicker(0,0,60,50,0){}

template <class T>
ColorPicker<T>::~ColorPicker() {
	// TODO Auto-generated destructor stub
}


//template class ColorPicker<char>;
template class ColorPicker<unsigned char>;

//template class ColorPicker<int>;
//template class ColorPicker<unsigned int>;

//template class ColorPicker<long>;
//template class ColorPicker<unsigned long>;

template class ColorPicker<float>;
//template class ColorPicker<double>;
