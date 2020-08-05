/*
 * RadioButton.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Nr5
 */

#ifndef UI_RADIOBUTTON_H_
#define UI_RADIOBUTTON_H_

#include "Panel.h"
#include <vector>
template <class T>
struct ButtonGroup{
	void(*onchange)(T* oldvalue,T* newvalue)=0;
	T* value=0;
	ButtonGroup(T* value): value(value){};
};
template <class T>
class RadioButton: public Panel {

public:
	T value;
	ButtonGroup<T> *group;

	RadioButton(int x,int y,int width,int height,T value,ButtonGroup<T> *group):
		Panel(x,y,width,height,0),	value(value), group(group) {
		mouselistener=[](Panel* p,SDL_Event,int x,int y){
			RadioButton<T>* radio=(RadioButton<T>*)p;
			if(radio->group->onchange)	radio->group->onchange(radio->group->value,&radio->value);
			*radio->group->value=radio->value;
			return true;
		};
	}

	virtual ~RadioButton(){};
};
#endif /* UI_RADIOBUTTON_H_ */
