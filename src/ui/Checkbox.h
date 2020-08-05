/*
 * Checkbox.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Nr5
 */

#ifndef UI_CHECKBOX_H_
#define UI_CHECKBOX_H_

#include "Panel.h"

class Checkbox: public Panel {
public:
	unsigned char* state=0;
	unsigned char  bitflag=1;
	
	mouseeventlistener checkboxclicked;
	Checkbox();
	Checkbox(int x,int y,int size);

	virtual ~Checkbox();
};

#endif /* UI_CHECKBOX_H_ */
