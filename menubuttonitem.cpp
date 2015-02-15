#include "menubuttonitem.h"
#include "define.h"

Texture* MenuButtonItem::m_commonTexture = new Texture((TEXTURE_PATH "case.png"));
Texture* MenuButtonItem::m_commonOverTexture = new Texture((TEXTURE_PATH "case_over.png"));
Texture* MenuButtonItem::m_commonClickTexture = m_commonOverTexture;
Texture* MenuButtonItem::m_commonCurrentTexture = new Texture((TEXTURE_PATH "case_current.png"));;

MenuButtonItem::MenuButtonItem(int x, int y, int width, int height, Menu* menu, BlockInfo* data, bool isCurrent) : MenuButton(x, y, width, height, menu, "", 0, false, m_commonTexture, m_commonOverTexture, m_commonClickTexture) {
	SetData(data);

	m_texture = m_commonTexture;
	m_isCurrent = isCurrent;
}

MenuButtonItem::~MenuButtonItem() {

}

BlockInfo* MenuButtonItem::GetData() {
	return m_data;
}

void MenuButtonItem::SetData(BlockInfo* data) {
	m_dragDrop = data != 0;
	m_data = data;
}

void MenuButtonItem::SetCurrent(bool enable)
{
	m_isCurrent = enable;
	if(enable)
		m_texture = m_commonCurrentTexture;
	else
		m_texture = m_normalTexture;
}

void MenuButtonItem::OnDrop(int x, int y) {
	if(m_dragDrop)
		MenuCurrentItem::GetInstance()->SetData(x, y, m_data);

	if(m_isCurrent)
		m_texture = m_commonCurrentTexture;
	else
		m_texture = m_normalTexture;
}

void MenuButtonItem::OnRelease(bool hit)
{
	MenuButton::OnRelease(hit);

	if(m_isCurrent)
		m_texture = m_commonCurrentTexture;
	else
		m_texture = m_normalTexture;
}


void MenuButtonItem::LostOver()
{
	if(m_isCurrent)
		m_texture = m_commonCurrentTexture;
	else
		m_texture = m_normalTexture;
}


#define BORDER 3

void MenuButtonItem::Draw() {
	MenuButton::Draw();

	if(m_data == 0)
		return;

	BlockInfoEncapsuler::GetAtlas()->Bind();

	glLoadIdentity();
	glTranslated(m_draggedX, m_draggedY, 0);

	float u = m_data->GetUC();
	float v = m_data->GetVC();
	float w = m_data->GetW();

	glBegin(GL_QUADS);
	glTexCoord2f(u, v);
	glVertex2i(BORDER, BORDER);
	glTexCoord2f(u + w, v);
	glVertex2i(m_width - BORDER, BORDER);
	glTexCoord2f(u + w, v + w);
	glVertex2i(m_width - BORDER, m_height - BORDER);
	glTexCoord2f(u, v + w);
	glVertex2i(BORDER, m_height - BORDER);
	glEnd();
}
