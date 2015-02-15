/*
 * menubuttoncoeur.cpp
 *
 *  Created on: Feb 29, 2012
 *      Author: j-s
 */

#include "menubuttoncoeur.h"
#include "engine.h"

Texture* MenuButtonCoeur::m_commonTexture = new Texture(TEXTURE_PATH "heart.png");

MenuButtonCoeur::MenuButtonCoeur(int x, int y, Menu* menu)
: MenuButton(x, y, COEUR_SIZE, COEUR_SIZE, menu,"", 16, false, m_commonTexture,m_commonTexture,m_commonTexture){

}
