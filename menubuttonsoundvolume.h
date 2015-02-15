/*
 * menubuttonsoundvolume.h
 *
 *  Created on: Feb 27, 2012
 *      Author: j-r
 */

#ifndef MENUBUTTONSOUNDVOLUME_H_
#define MENUBUTTONSOUNDVOLUME_H_

#include "menubutton.h"

class MenuButtonSoundVolume : public MenuButton {
public:
	MenuButtonSoundVolume(int x, int y, int width, int height, Menu* menu, const char* text = "Bruits: ", int fontSize = 16);
	~MenuButtonSoundVolume();
protected:
	void Synchronize();
	virtual void OnRelease(bool hit);
	int m_index;
	static float m_values[];
	static const char* m_suffix[];
	const char* m_startName;
};


#endif /* MENUBUTTONSOUNDVOLUME_H_ */
