/*
 * menubuttonviewdistance.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: j-r
 */

#include "menubuttonmusicvolume.h"
#include "preferences.h"

float MenuButtonMusicVolume::m_values[] = {1.f, 0.7f, 0.3f, 0.f};
const char* MenuButtonMusicVolume::m_suffix[] = { "Fort", "Moyen", "Faible", "Mute" };


MenuButtonMusicVolume::MenuButtonMusicVolume(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize)
: MenuButton(x, y, width, height, menu, text, fontSize), m_startName(text) {
	Synchronize();
}

MenuButtonMusicVolume::~MenuButtonMusicVolume() {
}

void MenuButtonMusicVolume::Synchronize() {
	float volume = Preferences::GetMusicVolume();

	m_index = 0;

	for(int i = 0; i < 4; ++i) {
		if(m_values[i] == volume) {
			m_index = i;
			break;
		}
	}

	m_text = std::string(m_startName).append(m_suffix[m_index]);
}

void MenuButtonMusicVolume::OnRelease(bool hit) {
	MenuButton::OnRelease(hit);

	if(hit) {
		Synchronize();
		m_index = (m_index + 1) % 4;
		m_text = std::string(m_startName).append(m_suffix[m_index]);
		Preferences::SetMusicVolume(m_values[m_index]);
	}
}
