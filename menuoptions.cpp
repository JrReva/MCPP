/*
 * menuoptions.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menuoptions.h"
#include "menubuttonviewdistance.h"
#include "menubuttonquitmenu.h"
#include "menubuttonmusicvolume.h"
#include "menubuttonsoundvolume.h"

MenuOptions* MenuOptions::m_instance = 0;

MenuOptions::MenuOptions(int windowX, int windowY) : Menu(650, 366, windowX, windowY, 4, true) {

}

MenuOptions* MenuOptions::GetInstance() {
	return m_instance;
}

MenuOptions* MenuOptions::Instanciate(int windowX, int windowY) {
	m_instance = new MenuOptions(windowX, windowY);
	return m_instance;
}

void MenuOptions::InitButtons() {
	int width = m_width - 50;
	int height = m_height / 4 - 25;


	
	delete m_buttons[0];
	m_buttons[0] = new MenuButtonViewDistance(
			m_posX + 25,
			m_posY + m_height - height - 20,
			width,
			height,
			this,
			"Distance de vue: ", 30);
	
	delete m_buttons[1];
	m_buttons[1] = new MenuButtonMusicVolume(
			m_posX + 25,
			m_posY + m_height - (height * 2) - 40,
			width,
			height,
			this,
			"Musique: ", 30);
	
	delete m_buttons[2];
	m_buttons[2] = new MenuButtonSoundVolume(
			m_posX + 25,
			m_posY + m_height - (height * 3) - 60,
			width,
			height,
			this,
			"Bruits: ", 30);
	
	delete m_buttons[3];
	m_buttons[3] = new MenuButtonQuitMenu(
			m_posX + 25,
			m_posY + m_height - (height * 4) - 80,
			width,
			height,
			this,
			"Retour au jeu", 30);
}

