/*
 * menubuttonviewdistance.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#include "menubuttonviewdistance.h"
#include "preferences.h"

int MenuButtonViewDistance::m_values[] = {64, 128, 256, 512};
float MenuButtonViewDistance::m_fogValues[] = {0.02, 0.01, 0.005, 0.0025};
const char* MenuButtonViewDistance::m_suffix[] = { "Petite", "Moyenne", "Grande", "Maximale" };


MenuButtonViewDistance::MenuButtonViewDistance(int x, int y, int width, int height, Menu* menu, const char* text, int fontSize)
: MenuButton(x, y, width, height, menu, text, fontSize), m_startName(text) {
	Synchronize();
}

MenuButtonViewDistance::~MenuButtonViewDistance() {
}

void MenuButtonViewDistance::Synchronize() {
	int distance = Preferences::GetLoadDistance();

	m_index = 0;

	for(int i = 0; i < 4; ++i) {
		if(m_values[i] == distance) {
			m_index = i;
			break;
		}
	}

	m_text = std::string(m_startName).append(m_suffix[m_index]);
}

void MenuButtonViewDistance::OnRelease(bool hit) {
	MenuButton::OnRelease(hit);
	if(hit) {
		Synchronize();
		m_index = (m_index + 1) % 4;
		m_text = std::string(m_startName).append(m_suffix[m_index]);
		Preferences::SetLoadDistance(m_values[m_index]);
		Preferences::SetFogDensity(m_fogValues[m_index]);
	}
}
