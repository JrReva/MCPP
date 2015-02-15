/*
 * menupause.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menupause.h"
#include "menubuttonquitmenu.h"
#include "menubuttonquitgame.h"
#include "menubuttonopenoptions.h"

MenuPause* MenuPause::m_instance = 0;

MenuPause::MenuPause(int windowX, int windowY) : Menu(650, 366, windowX, windowY, 3, true) {

}

MenuPause* MenuPause::GetInstance() {
	return m_instance;
}

MenuPause* MenuPause::Instanciate(int windowX, int windowY) {
	m_instance = new MenuPause(windowX, windowY);
	return m_instance;
}

void MenuPause::InitButtons() {
	int width = m_width - 50;
	int height = (m_height / 3) - 25 ;
	
	delete m_buttons[0];
	m_buttons[0] = new MenuButtonQuitMenu(
			m_posX + 25,
			m_posY + m_height - height - 20,
			width,
			height,
			this,
			"Retour au jeu", 30);
	
	delete m_buttons[1];
	m_buttons[1] = new MenuButtonOpenOptions(
			m_posX + 25,
			m_posY + m_height - (height * 2) - 40,
			width,
			height,
			this,
			"Options", 30);
	
	delete m_buttons[2];
	m_buttons[2] = new MenuButtonQuitGame(
			m_posX + 25,
			m_posY + m_height - (height * 3) - 60,
			width,
			height,
			this,
			"Quitter le jeu", 30);
}

