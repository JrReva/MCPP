/*
 * menubuttonquitgame.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONQUITGAME_H_
#define MENUBUTTONQUITGAME_H_

#include "menubutton.h"

class MenuButtonQuitGame : public MenuButton {
public:
	MenuButtonQuitGame(int x, int y, int width, int height, Menu* menu, const char* text = "Quitter", int fontSize = 16);
protected:
	virtual void OnRelease(bool hit);
};


#endif /* MENUBUTTONQUITGAME_H_ */
