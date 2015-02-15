#ifndef MENU_BUTTON_ITEM_H__
#define MENU_BUTTON_ITEM_H__
#include "menubutton.h"
#include "blockinfoencapsuler.h"
#include "menucurrentitem.h"

class MenuButtonItem : public MenuButton {
public:
	MenuButtonItem(int x, int y, int width, int height, Menu* menu, BlockInfo* data = 0, bool isCurrent = false);

	virtual ~MenuButtonItem();

	BlockInfo* GetData();
	void SetData(BlockInfo* data);
	void Draw();
	void SetCurrent(bool enable);
	bool IsCurrent() {return m_isCurrent;}
protected:
	virtual void OnDrop(int x, int y);
	virtual void OnRelease(bool hit);
	virtual void LostOver();
	BlockInfo* m_data;
	
	bool m_isCurrent;

	static Texture* m_commonTexture;
	static Texture* m_commonClickTexture;
	static Texture* m_commonOverTexture;
	static Texture* m_commonCurrentTexture;
};


#endif
