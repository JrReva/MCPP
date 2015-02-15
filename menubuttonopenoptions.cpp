/*
 * menubuttonopenoptions.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menubuttonopenoptions.h"
#include "menuoptions.h"

MenuButtonOpenOptions::MenuButtonOpenOptions(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize)
: MenuButton(x, y, width, height, menu, text, fontSize){
	
}

void MenuButtonOpenOptions::OnRelease(bool hit) {
	MenuButton::OnRelease(hit);

	if(hit)
		MenuOptions::GetInstance()->Show();
}
