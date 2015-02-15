#ifndef BLOCKINFO_H__
#define BLOCKINFO_H__

#include <string>
#include <iostream>
#include "define.h"

class BlockInfo
{
public:
    BlockInfo(BlockType type, const std::string& nom, float uc, float vc, float uu, float vu, float ub, float vb, float w, float h, bool walkable = false, bool transparent = false);
	BlockInfo(BlockType type, const std::string& nom, float uc, float vc, float uu, float vu, float w, float h, bool walkable = false, bool transparent = false);
	BlockInfo(BlockType type, const std::string& nom, float u, float v, float w, float h, bool walkable = false, bool transparent = false);
    ~BlockInfo();

    BlockType GetType() const;

    void SetDurability(int durability);
    int GetDurability() const;

	float GetUC() const;
	float GetVC() const;
	float GetUU() const;
	float GetVU() const;
	float GetUB() const;
	float GetVB() const;
	float GetW() const;

	void SetIntensity(float value);
	float GetIntensity();

	BlockType GetBlockType();
    void Show() const;

	bool IsTransparent() const;
	bool IsWalkable() const;

	std::string GetName() const;
private:
	bool m_transparent;
	bool m_walkable;

	float m_uc, m_vc, m_uu, m_vu, m_ub, m_vb, m_w, m_h,
		m_intensity;
	int m_durability;
	bool transparent;
    BlockType m_type;
    std::string m_name, m_nameTexture;

};

#endif // BLOCKINFO_H__
