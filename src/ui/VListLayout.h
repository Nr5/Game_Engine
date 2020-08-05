/*
 * VListLayout.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Nr5
 */

#ifndef UI_VLISTLAYOUT_H_
#define UI_VLISTLAYOUT_H_
#include <algorithm>

#include "Panel.h"
class V_List_Layout : public AbstractLayout {

public:
	enum ALIGN{
		H_ALIGN_LEFT,
		H_ALIGN_CENTER,
		H_ALIGN_RIGHT
	};
	int padding;
	char align;
	bool scalewidth;
	bool scaleheight;
	V_List_Layout(int padding,char align,bool scalewidth,bool scaleheight);
	virtual void resize(Panel* parent);
	virtual void add(Panel* parent,Panel* child);
	virtual void insert(Panel* parent,Panel* child, int index);
	virtual void remove(Panel* parent,Panel* child);
	virtual ~V_List_Layout();
};

#endif /* UI_VLISTLAYOUT_H_ */
