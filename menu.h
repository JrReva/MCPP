#ifndef MENU_H__
#define MENU_H__

#include "texture.h"

class MenuButton;

class Menu {
public:
	static Menu* GetCurrentMenu();
	static void SetCurrentMenu(Menu* menu);
	Menu(int width, int height, int windowX, int windowY, int itemNbr = 0, bool needPause = false, Texture* texture = m_communTexture);
	virtual ~Menu();

	virtual void Center(int windowX, int windowY);
	virtual void InitButtons() {};

	virtual void Show();
	virtual void Hide();
	virtual void Toggle();

	void MouseOver(int x, int y);
	void MouseClick(int x, int y);
	void MouseClickReleased(int x, int y);

	bool IsPauseNeeded();
	virtual bool IsShowed();

	void GetPosition(int& x, int& y, int& width, int& height);

	virtual void Draw();

	static void PrintText(unsigned int x, unsigned int y, unsigned int size, const std::string& t,  unsigned int width = 0, unsigned int height = 0);
protected:
	virtual void OnShow() { };
	virtual void OnHide() { };
	
	static Menu* m_current;
	bool m_needPause;
	std::vector<MenuButton*> m_buttons;
	
	MenuButton* m_buttonClicked;
	MenuButton* m_lastOver;

	int m_posX;
	int m_posY;
	int m_width;
	int m_height;

	Texture* m_texture;

private:
	static Texture* m_communTexture;
	static Texture* m_textureFont;
};

#endif
