#ifndef MENU_CURRENT_ITEM_H__
#define MENU_CURRENT_ITEM_H__

#include "menu.h"
#include "blockinfo.h"

class MenuCurrentItem : public Menu {
public:
	static MenuCurrentItem* GetInstance();
	static MenuCurrentItem* Instanciate(int windowX, int windowY);

	virtual void Center(int windowX, int windowY);
	virtual void InitButtons();

	virtual void Show() { }
	virtual void Hide() { }
	virtual bool IsShowed() { return true; }

	int GetCurrentItemIndex();
	BlockType GetCurrentItemBlockType();
	void SetCurrentItem(int index);
	bool SetData(int x, int y, BlockInfo* data);
protected:
	MenuCurrentItem(int windowX, int windowY);
	static MenuCurrentItem* m_instance;
};

#endif