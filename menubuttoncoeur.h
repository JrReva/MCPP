/*
 * menubuttonquitmenu.h
 *
 *  Created on: Feb 29, 2012
 *      Author: j-s
 */

#ifndef MENUBUTTONCOEUR_H_
#define MENUBUTTONCOEUR_H_

#include "menubutton.h"

class MenuButtonCoeur : public MenuButton {
public:
	MenuButtonCoeur(int x, int y, Menu* menu);

private:
	static Texture* m_commonTexture;
};


#endif /* MENUBUTTONCOEUR_H_ */