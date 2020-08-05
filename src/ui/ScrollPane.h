/*
 * ScrollPane.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Nr5
 */

#ifndef UI_SCROLLPANE_H_
#define UI_SCROLLPANE_H_

#include "Panel.h"

class ScrollPane: public Panel {
private:
public:
	Panel* viewport=0;
	Panel* v_handle=0;
	Panel* content=0;
	float scrollpos=0;
	ScrollPane();
	ScrollPane(int x,int y,int width,int height,int bgcolor);
	void add(Panel* p);
	virtual ~ScrollPane();
};

#endif /* UI_SCROLLPANE_H_ */
