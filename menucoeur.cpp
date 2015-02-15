#include "menucoeur.h"
#include "menubuttoncoeur.h"
#include "define.h"

MenuCoeur* MenuCoeur::m_instance = 0;

MenuCoeur* MenuCoeur::GetInstance() {
	return m_instance;
}

MenuCoeur* MenuCoeur::Instanciate(int windowX, int windowY) {
	m_instance = new MenuCoeur(windowX, windowY);
	return m_instance;
}

MenuCoeur::MenuCoeur(int windowX, int windowY) : Menu(COEUR_SIZE * 10, COEUR_SIZE, windowX, windowY, 10, false, 0),m_nbcoeur(10) {
}

void MenuCoeur::Center(int windowX, int windowY) {
	Menu::Center(windowX, m_height+150);
}

void MenuCoeur::InitButtons() {
	for(int i = 0; i < 10; ++i) {
		int px = i * COEUR_SIZE + m_posX;
		int py = m_posY;
		
		delete m_buttons[i];
		if(i < m_nbcoeur)
			m_buttons[i] = new MenuButtonCoeur(px, py, this);
		else
			m_buttons[i] = new MenuButtonCoeur(-2000000,-2000000, this);
	}
}

int MenuCoeur::GetNbCoeur()
{
	return m_nbcoeur;
}

void MenuCoeur::SetNbCoeur(int nbcoeur)
{
	m_nbcoeur = nbcoeur;

	InitButtons();
}