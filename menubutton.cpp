#include "menubutton.h"

Texture* MenuButton::m_communNormalTexture = new Texture(TEXTURE_PATH "boutton.png");
Texture* MenuButton::m_communClickTexture = new Texture(TEXTURE_PATH "boutton_appuyer.png");
Texture* MenuButton::m_communOverTexture = new Texture(TEXTURE_PATH "boutton_over.png");

MenuButton::MenuButton(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize, bool dragDrop, Texture* normalTexture, Texture* overTexture, Texture* clickTexture) :
m_width(width), m_height(height), m_menu(menu), m_posX(x), m_posY(y), m_draggedX(x), m_draggedY(y), m_texture(normalTexture), m_clickTexture(clickTexture), m_normalTexture(normalTexture), m_overTexture(overTexture), m_text(text), m_fontSize(fontSize), m_dragDrop(dragDrop) {
}

MenuButton::~MenuButton() {

}

bool MenuButton::IntersectWith(int x, int y) {
	if(x < m_posX || x > m_posX + m_width)
		return false;
	if(y < m_posY || y > m_posY + m_height)
		return false;
	return true;
}

bool MenuButton::MouseOver(int x, int y, bool forced) {
	if(forced) {
		OnOver();

		if(m_dragDrop) {
			m_draggedX += (x - m_lastMouseX);
			m_draggedY += (y - m_lastMouseY);
		}

		m_lastMouseX = x;
		m_lastMouseY = y;

		OnDrag();
		return true;
	}
	else
		if(IntersectWith(x, y)) {
			OnOver();

			m_lastMouseX = x;
			m_lastMouseY = y;

			return true;
		}
		else
			LostOver();
	return false;
}

bool MenuButton::MouseClick(int x, int y) {
	if(IntersectWith(x, y)) {
		OnClick();
		return true;
	}

	return false;
}

bool MenuButton::MouseClickReleased(int x, int y) {
	if(m_dragDrop) {
		m_draggedX = x;
		m_draggedY = y;
		OnDrop(x, y);
		m_draggedX = m_posX;
		m_draggedY = m_posY;
		OnRelease(true);
		return true;
	} else {
		OnRelease(IntersectWith(x, y));
		return true;
	}
}

Texture* MenuButton::GetTextureToDraw() {
	return m_texture;
}

void MenuButton::GetPosition(int& x, int& y, int& width, int& height) {
	x = m_draggedX;
	y = m_draggedY;
	width = m_width;
	height = m_height;
}

void MenuButton::OnOver() {
	m_texture = m_overTexture;
}

void MenuButton::LostOver() {
	m_texture = m_normalTexture;
}

void MenuButton::OnClick() {
	m_texture = m_clickTexture;
}

void MenuButton::OnRelease(bool hit) {
	m_texture = m_normalTexture;
}

void MenuButton::Draw() {
	if(m_texture == 0) {
		return;
	}

	if(!m_texture->IsValid()) {
		m_texture->Load();
	}

	m_texture->Bind();
	glLoadIdentity();
	glTranslated(m_draggedX, m_draggedY, 0);

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

	if(m_text.length() > 0) {
		Menu::PrintText(m_posX, m_posY, m_fontSize, m_text, m_width, m_height);
	}
}

void MenuButton::SetPosition(int x, int y) {
	m_draggedX = m_posX = x;
	m_draggedY = m_posY = y;
}
