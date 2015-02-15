/*
 * menubuttonopenoptions.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONOPENOPTIONS_H_
#define MENUBUTTONOPENOPTIONS_H_

#include "menubutton.h"

class MenuButtonOpenOptions : public MenuButton {
public:
	MenuButtonOpenOptions(int x, int y, int width, int height, Menu* menu, const char* text = "Options", int fontSize = 16);
protected:
	virtual void OnRelease(bool hit);
};


#endif /* MENUBUTTONOPENOPTIONS_H_ */
