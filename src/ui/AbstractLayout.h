/*
 * AbstractLayout.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Nr5
 */

#ifndef UI_ABSTRACTLAYOUT_H_
#define UI_ABSTRACTLAYOUT_H_
class Panel;
class AbstractLayout {
public:
	virtual void resize(Panel* parent)=0;
	virtual void add(Panel* parent,Panel* child)=0;
	virtual void insert(Panel* parent,Panel* child, int index)=0;
	virtual void remove(Panel* parent,Panel* child)=0;
	virtual ~AbstractLayout(){};
};

#endif /* UI_ABSTRACTLAYOUT_H_ */
