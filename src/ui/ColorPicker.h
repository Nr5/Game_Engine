/*
 * ColorPicker.h
 *
 *  Created on: Nov 18, 2018
 *      Author: Nr5
 */

#ifndef UI_COLORPICKER_H_
#define UI_COLORPICKER_H_
#include <limits>
#include "Panel.h"

template <class T>
class ColorPicker: public Panel {
public:

	T value[4]={1,1,1,1};
	T *color=0;

	float brightness=1;
	float opacity=1;
	
	Panel* colorBall;
	Panel* brightnessPicker;
	Panel* opacityPicker;
	Panel* preview;
	ColorPicker();
	ColorPicker(int x,int y,int width,int height,int bgcolor);

	//virtual void draw(int,int,int,int,int,int);
	//bool pickColor(Panel *p,SDL_Event event,int x,int y);
	
	virtual ~ColorPicker();
};

#endif /* UI_COLORPICKER_H_ */
