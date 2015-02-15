/*
 * menuoptions.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef MENUOPTIONS_H_
#define MENUOPTIONS_H_

#include "menu.h"
#include "texture.h"

class MenuOptions : public Menu {
public:
	static MenuOptions* GetInstance();
	static MenuOptions* Instanciate(int windowX, int windowY);
	void InitButtons();
private:
	MenuOptions(int windowX, int windowY);

	static MenuOptions* m_instance;
};


#endif /* MENUOPTIONS_H_ */
