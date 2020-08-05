/*
 * Slider.h
 *
 *  Created on: Nov 18, 2018
 *      Author: Nr5
 */

#ifndef UI_SLIDER_H_
#define UI_SLIDER_H_

#include "Panel.h"
template <class T>
class Slider: public Panel {
public:
	T* value=0;
	T min;
	T max;
	Slider(int x,int y,int width,int height,int bgcolor);
	Slider();
	void setValue(T* value);
	void setValue(T value);
	void getlimits();
	static bool slidermouselistener(Panel *p,SDL_Event event,int x,int y);
	static bool slidermousedraglistener(Panel *p,SDL_Event event,int x,int y,int,int);
	
	static void sliderrender(Panel* p);
	
	
	
	
	
	virtual ~Slider();
};

#endif /* UI_SLIDER_H_ */
