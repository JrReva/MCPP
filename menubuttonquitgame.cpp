/*
 * menubuttonquitgame.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menubuttonquitgame.h"
#include "engine.h"

MenuButtonQuitGame::MenuButtonQuitGame(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize)
: MenuButton(x, y, width, height, menu, text, fontSize){

}

void MenuButtonQuitGame::OnRelease(bool hit) {
	MenuButton::OnRelease(hit);

	if(hit)
		Engine::GetInstance()->Stop();
}
