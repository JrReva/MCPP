/*
 * menuitem.cpp
 *
 *  Created on: Feb 21, 2012
 *      Author: j-r
 */

#include "menuitem.h"
#include "blockinfoencapsuler.h"
#include "menubuttonitem.h"

MenuItem* MenuItem::m_instance = 0;

MenuItem::MenuItem(int windowX, int windowY) : Menu(650, 366, windowX, windowY, BTYPE_LAST - 1, true) {

}

MenuItem* MenuItem::GetInstance() {
	return m_instance;
}

MenuItem* MenuItem::Instanciate(int windowX, int windowY) {
	m_instance = new MenuItem(windowX, windowY);
	return m_instance;
}

void MenuItem::InitButtons() {
	int numberByLine = (m_width - 6) / ITEM_CASE_SIZE;

	BlockInfoEncapsuler* encaps = BlockInfoEncapsuler::GetInstance();

	for(int i = 1; i < BTYPE_LAST; ++i) {
			int x = (i - 1) % numberByLine;
			int y = (i - 1) / numberByLine;

			int px = x * ITEM_CASE_SIZE + 15 + m_posX;
			int py = (m_posY + m_height - ITEM_CASE_SIZE - 15) - (y * ITEM_CASE_SIZE);
			
		if(m_buttons[i - 1] == 0) {
			m_buttons[i - 1] = new MenuButtonItem(
				px, py, ITEM_CASE_SIZE, ITEM_CASE_SIZE, this, (*encaps)[i]);
		}
		else {
			m_buttons[i - 1]->SetPosition(px, py);
		}
	}
}
