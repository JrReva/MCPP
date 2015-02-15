#ifndef BLOCKINFOENCAPSULER_H__
#define BLOCKINFOENCAPSULER_H__

#include "define.h"
#include "blockinfo.h"
#include "textureatlas.h"

enum BLOCK_TYPE {BTYPE_AIR, BTYPE_DIRT, BTYPE_GRASS, BTYPE_WATER, BTYPE_ROCK, BTYPE_BRICK, BTYPE_FROM,BTYPE_GLASS,BTYPE_BEDROCK,BTYPE_LEAF,BTYPE_WOOD, BTYPE_SAND, BTYPE_LAST};

class BlockInfoEncapsuler
{
public:
	static BlockInfoEncapsuler* GetInstance();
	static TextureAtlas* GetAtlas();
	static void LoadRessources();

	~BlockInfoEncapsuler();
	void AddBlockInfo(BlockInfo* bi);

	BlockInfo* operator[](BlockType type);

private:
	BlockInfoEncapsuler();
	BlockInfo* m_types[BTYPE_LAST];
	static BlockInfoEncapsuler* m_instance;
	static TextureAtlas* m_atlas;
};


#endif // BLOCKINFOENCAPSULER_H__
