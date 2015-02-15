/*
 * menubuttonquitmenu.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menubuttonquitmenu.h"

MenuButtonQuitMenu::MenuButtonQuitMenu(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize)
: MenuButton(x, y, width, height, menu, text, fontSize){

}

void MenuButtonQuitMenu::OnRelease(bool hit) {
	MenuButton::OnRelease(hit);
	if(hit) {
		m_menu->Hide();
	}
}
