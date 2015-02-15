#include "menu.h"
#include "menubutton.h"

Menu* Menu::m_current = 0;
Texture* Menu::m_textureFont = new Texture(TEXTURE_PATH "font.bmp");
Texture* Menu::m_communTexture = new Texture(TEXTURE_PATH "menu_fond.png");

Menu* Menu::GetCurrentMenu() {
	return m_current;
}

void Menu::SetCurrentMenu(Menu* menu) {
	if(m_current != menu) {
		Menu* current = m_current;
		m_current = 0;

		if(current != 0)
			current->Hide();

		m_current = menu;

		if(m_current != 0) {
			m_current->Show();
		}
	}
}

Menu::Menu(int width, int height, int windowX, int windowY, int itemNbr, bool needPause, Texture* texture) : m_needPause(needPause), m_texture(texture), m_buttonClicked(0), m_buttons(itemNbr), m_width(width), m_height(height) {
	Center(windowX, windowY);
}

void Menu::Toggle() {
	if(m_current == this)
		Hide();
	else
		Show();
}

void Menu::Show() {
	SetCurrentMenu(this);
	OnShow();
}

void Menu::Hide() {
	if(m_current == this) {
		SetCurrentMenu(0);
	} else {
		OnHide();
	}
}

void Menu::MouseOver(int x, int y) {
	if(m_buttonClicked != 0) {
		m_buttonClicked->MouseOver(x, y, true);
	} else {
		for(uint32 i = 0; i < m_buttons.size(); ++i) {
			m_buttons[i]->MouseOver(x, y);
		}
	}
}

void Menu::MouseClick(int x, int y) {
	for(uint32 i = 0; i < m_buttons.size(); ++i) {
		if(m_buttons[i]->MouseClick(x, y)) {
			m_buttonClicked = m_buttons[i];
			return;
		}
	}
}

void Menu::MouseClickReleased(int x, int y){
	if(m_buttonClicked != 0) {
		m_buttonClicked->MouseClickReleased(x, y);
		m_buttonClicked = 0;
	}
}

bool Menu::IsPauseNeeded() {
	return m_needPause;
}

bool Menu::IsShowed() {
	return m_current == this;
}

void Menu::Center(int windowX, int windowY) {
	m_posX = windowX / 2 - m_width / 2;
	m_posY = windowY / 2 - m_height / 2;

	InitButtons();
}

void Menu::Draw() {
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if(m_texture != 0) {
		if(!m_texture->IsValid())
			m_texture->Load();

		m_texture->Bind();

		glLoadIdentity();
		glTranslated(m_posX, m_posY, 0);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		glTexCoord2f(1, 0);
		glVertex2i(m_width, 0);
		glTexCoord2f(1, 1);
		glVertex2i(m_width, m_height);
		glTexCoord2f(0, 1);
		glVertex2i(0, m_height);
		glEnd();
	}

	for(uint32 i = 0; i < m_buttons.size(); ++i) {
		if(m_buttons[i] != m_buttonClicked) {
			m_buttons[i]->Draw();
		}
	}

	if(m_buttonClicked != 0)
		m_buttonClicked->Draw();
}

void Menu::PrintText(unsigned int x, unsigned int y, unsigned int size, const std::string& t,  unsigned int width, unsigned int height)
{
	if(!m_textureFont->IsValid())
		m_textureFont->Load();

	m_textureFont->Bind();

	int startX = x;
	int startY = y;

	if(width > 0) {
		startX += ((width - (size * t.length() * 0.65f)) / 2);
	}
	if(height > 0) {
		startY += ((height - size) / 2);
	}
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glLoadIdentity();
	glTranslated(startX, startY, 0);
	for (unsigned int i = 0; i < t.length(); ++i)
	{
		float left = (float)((t[i] - 32) % 16) / 16.0f;
		float top = (float)((t[i] - 32) / 16) / 16.0f;

		top += 0.5f;

		glBegin(GL_QUADS);
		glTexCoord2f(left, 1.0f - top - 0.0625f);
		glVertex2f(0, 0);
		glTexCoord2f(left + 0.0625f, 1.0f - top - 0.0625f);
		glVertex2f(size, 0);
		glTexCoord2f(left + 0.0625f, 1.0f - top);
		glVertex2f(size, size);
		glTexCoord2f(left, 1.0f - top);
		glVertex2f(0, size);
		glEnd();

		glTranslated(size * 0.65f, 0, 0);
	}
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

Menu::~Menu() {
	for(int i = 0; i < m_buttons.size(); ++i) {
		delete m_buttons[i];
	}
}