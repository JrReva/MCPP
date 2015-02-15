#include "menucurrentitem.h"
#include "menubuttonitem.h"
#include "define.h"

MenuCurrentItem* MenuCurrentItem::m_instance = 0;

MenuCurrentItem* MenuCurrentItem::GetInstance() {
	return m_instance;
}

MenuCurrentItem* MenuCurrentItem::Instanciate(int windowX, int windowY) {
	m_instance = new MenuCurrentItem(windowX, windowY);
	return m_instance;
}

MenuCurrentItem::MenuCurrentItem(int windowX, int windowY) : Menu(ITEM_CASE_SIZE * NUMBER_CURRENT_ITEMS, ITEM_CASE_SIZE, windowX, windowY, NUMBER_CURRENT_ITEMS, false, 0) {
}

void MenuCurrentItem::Center(int windowX, int windowY) {
	Menu::Center(windowX, m_height);
}

void MenuCurrentItem::InitButtons() {
	for(int i = 0; i < NUMBER_CURRENT_ITEMS; ++i) {
		int px = i * ITEM_CASE_SIZE + m_posX;
		int py = m_posY;

		if(m_buttons[i] == 0) {
			delete m_buttons[i];
			m_buttons[i] = new MenuButtonItem(px, py, ITEM_CASE_SIZE, ITEM_CASE_SIZE, this, (*BlockInfoEncapsuler::GetInstance())[i + 1]);
		} else {
			m_buttons[i]->SetPosition(px, py);
		}
	}

	if(GetCurrentItemIndex() < 0)
		SetCurrentItem(0);
}

bool MenuCurrentItem::SetData(int x, int y, BlockInfo* data) {
	if(x < m_posX || x > m_posX + m_width)
		return false;

	if(y < m_posY || y > m_posY + m_height)
		return false;

	int i = ((x - m_posX) / ITEM_CASE_SIZE);

	((MenuButtonItem*)m_buttons[i])->SetData(data);

	return true;
}

void MenuCurrentItem::SetCurrentItem(int index)
{
	for(int i = 0; i < NUMBER_CURRENT_ITEMS; ++i) 
	{
		if(((MenuButtonItem*)m_buttons[i])->IsCurrent())
		{
			((MenuButtonItem*)m_buttons[i])->SetCurrent(false);
		}
	}
	((MenuButtonItem*)m_buttons[index])->SetCurrent(true);
}

BlockType MenuCurrentItem::GetCurrentItemBlockType()
{
	BlockType type = BTYPE_GRASS;
	for(int i = 0; i < NUMBER_CURRENT_ITEMS; ++i) 
	{
		if(((MenuButtonItem*)m_buttons[i])->IsCurrent())
		{
			return ((MenuButtonItem*)m_buttons[i])->GetData()->GetType();
		}
	}
	return type;
}

int MenuCurrentItem::GetCurrentItemIndex()
{
	for(int i = 0; i < NUMBER_CURRENT_ITEMS; ++i) 
	{
		if(((MenuButtonItem*)m_buttons[i])->IsCurrent())
		{
			return i;
		}
	}
	return -1;
}
