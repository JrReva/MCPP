/*
 * menupause.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUPAUSE_H_
#define MENUPAUSE_H_

#include "menu.h"
#include "texture.h"

class MenuPause : public Menu {
public:
	static MenuPause* GetInstance();
	static MenuPause* Instanciate(int windowX, int windowY);
	void InitButtons();
private:
	MenuPause(int windowX, int windowY);
	static MenuPause* m_instance;
};


#endif /* MENUPAUSE_H_ */
