#ifndef MENU_BUTTON_H__
#define MENU_BUTTON_H__

#include "menu.h"
#include "texture.h"

class MenuButton {
public:
	MenuButton(int x, int y, int width, int height, Menu* menu, const char* text = "", int fontSize = 16, bool dragDrop = false, Texture* normalTexture = m_communNormalTexture, Texture* overTexture = m_communOverTexture, Texture* clickTexture = m_communClickTexture);
	virtual ~MenuButton();

	bool MouseOver(int x, int y, bool forced = false);
	bool MouseClick(int x, int y);
	bool MouseClickReleased(int x, int y);

	Texture* GetTextureToDraw();
	void GetPosition(int& x, int& y, int& width, int& height);
	bool IntersectWith(int x, int y);

	virtual void Draw();
	void SetPosition(int x, int y);

protected:
	virtual void OnOver();
	virtual void LostOver();
	virtual void OnClick();
	virtual void OnDrag() { };
	virtual void OnDrop(int x, int y) { };
	virtual void OnRelease(bool hit);

	Texture* m_texture;
	Texture* m_normalTexture;
	Texture* m_overTexture;
	Texture* m_clickTexture;

	static Texture* m_communNormalTexture;
	static Texture* m_communOverTexture;
	static Texture* m_communClickTexture;

	int m_posX, m_posY, m_width, m_height;
	int m_draggedX, m_draggedY;
	int m_lastMouseX, m_lastMouseY;

	bool m_dragDrop;

	std::string m_text;
	int m_fontSize;

	Menu* m_menu;
private:
	bool m_inDrag;
};

#endif
