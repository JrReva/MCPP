/*
 * menubuttonquitmenu.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONQUITMENU_H_
#define MENUBUTTONQUITMENU_H_

#include "menubutton.h"

class MenuButtonQuitMenu : public MenuButton {
public:
	MenuButtonQuitMenu(int x, int y, int width, int height, Menu* menu, const char* text = "Retour", int fontSize = 16);
protected:
	virtual void OnRelease(bool hit);
};


#endif /* MENUBUTTONQUITMENU_H_ */
