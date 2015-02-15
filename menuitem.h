/*
 * menuitem.h
 *
 *  Created on: Feb 21, 2012
 *      Author: j-r
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "menu.h"
#include "texture.h"

class MenuItem : public Menu {
public:
	static MenuItem* GetInstance();
	static MenuItem* Instanciate(int windowX, int windowY);
	void InitButtons();
private:
	MenuItem(int windowX, int windowY);

	static MenuItem* m_instance;
};


#endif /* MENUITEM_H_ */
