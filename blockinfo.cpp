#include "blockinfo.h"

//Initialise toutes les faces sur la même texture.
BlockInfo::BlockInfo(BlockType type, const std::string& nom, float uc, float vc, float w, float h, bool walkable, bool transparent) 
	: m_type(type), m_name(nom),m_intensity(0.2f), m_durability(1), m_uc(uc), m_vc(vc), m_uu(uc), m_vu(vc), m_ub(uc), m_vb(vc), m_w(w), m_h(h), m_walkable(walkable), m_transparent(transparent)
{
}

//initialise le dessus et le bas avec une texture, alors que les cotés ont leur texture
BlockInfo::BlockInfo(BlockType type, const std::string& nom, float uc, float vc, float uu, float vu, float w, float h, bool walkable, bool transparent) 
	: m_type(type), m_name(nom),m_intensity(0.2f), m_durability(1), m_uc(uc), m_vc(vc), m_uu(uu), m_vu(vu), m_ub(uu), m_vb(vu), m_w(w), m_h(h), m_walkable(walkable), m_transparent(transparent)
{
}

//initialise le dessus avec une texture, le bas avec une autre texture, alors que les cotés ont leur texture
BlockInfo::BlockInfo(BlockType type, const std::string& nom, float uc, float vc, float uu, float vu, float ub, float vb, float w, float h, bool walkable, bool transparent) 
	: m_type(type), m_name(nom), m_durability(1), m_uc(uc), m_vc(vc), m_uu(uu), m_vu(vu), m_ub(ub), m_vb(vb), m_w(w), m_h(h), m_walkable(walkable), m_transparent(transparent),
	m_intensity(0.2f)
{
}

BlockInfo::~BlockInfo()
{
}

std::string BlockInfo::GetName() const {
	return m_name;
}

BlockType BlockInfo::GetType() const
{
    return m_type;
}

float BlockInfo::GetIntensity()
{
	return m_intensity;
}

void BlockInfo::SetIntensity(float value)
{
	m_intensity = value;
}

void BlockInfo::SetDurability(int durability)
{
    m_durability = durability;
}

float BlockInfo::GetUC() const
{
	return m_uc;
}

float BlockInfo::GetVC() const
{
	return m_vc;
}

float BlockInfo::GetUU() const
{
	return m_uu;
}

float BlockInfo::GetVU() const
{
	return m_vu;
}

float BlockInfo::GetUB() const
{
	return m_ub;
}

float BlockInfo::GetVB() const
{
	return m_vb;
}

float BlockInfo::GetW() const
{
	return m_w;
}

int BlockInfo::GetDurability() const
{
    return m_durability;
}

void BlockInfo::Show() const
{
    std::cout << "Type: " << m_type << std::endl;
    std::cout << "Nom: " << m_name << std::endl;
    std::cout << "Durabilite: " << m_durability << std::endl;
}

bool BlockInfo::IsTransparent() const {
	return m_transparent;
}

bool BlockInfo::IsWalkable() const {
	return m_walkable;
}
