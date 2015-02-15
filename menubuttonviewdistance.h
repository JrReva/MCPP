/*
 * menubuttonviewdistance.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONVIEWDISTANCE_H_
#define MENUBUTTONVIEWDISTANCE_H_

#include "menubutton.h"

class MenuButtonViewDistance : public MenuButton {
public:
	MenuButtonViewDistance(int x, int y, int width, int height, Menu* menu, const char* text = "Distance de vue: ", int fontSize = 16);
	~MenuButtonViewDistance();
protected:
	void Synchronize();
	virtual void OnRelease(bool hit);
	int m_index;
	static int m_values[];
	static float m_fogValues[];
	static const char* m_suffix[];
	const char* m_startName;
};


#endif /* MENUBUTTONVIEWDISTANCE_H_ */
