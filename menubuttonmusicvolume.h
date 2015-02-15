/*
 * menubuttonmusicvolume.h
 *
 *  Created on: Feb 27, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONMUSICVOLUME_H_
#define MENUBUTTONMUSICVOLUME_H_

#include "menubutton.h"

class MenuButtonMusicVolume : public MenuButton {
public:
	MenuButtonMusicVolume(int x, int y, int width, int height, Menu* menu, const char* text = "Musique: ", int fontSize = 16);
	~MenuButtonMusicVolume();
protected:
	void Synchronize();
	virtual void OnRelease(bool hit);
	int m_index;
	static float m_values[];
	static const char* m_suffix[];
	const char* m_startName;
};


#endif /* MENUBUTTONMUSICVOLUME_H_ */
