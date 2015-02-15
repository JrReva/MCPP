#include "blockinfoencapsuler.h"

BlockInfoEncapsuler* BlockInfoEncapsuler::m_instance = 0;
TextureAtlas* BlockInfoEncapsuler::m_atlas = 0;

void BlockInfoEncapsuler::LoadRessources() {
	m_instance = new BlockInfoEncapsuler();
}

BlockInfoEncapsuler* BlockInfoEncapsuler::GetInstance() {
	return m_instance;
}

TextureAtlas* BlockInfoEncapsuler::GetAtlas() {
	return m_atlas;
}

BlockInfoEncapsuler::BlockInfoEncapsuler() {
	float u, v, w, h; // variable u, v, w, h; temporaire
	float cu, cv, cw, ch; // variable u, v, w, h; temporaire
	float bu, bv, bw, bh; // variable u, v, w, h; temporaire
	BlockInfo* bloc;

	m_atlas = new TextureAtlas(BTYPE_LAST);
	
	// Air
	bloc = new BlockInfo(BTYPE_AIR, "Air", 0, 0, 0, 0, true, true);
	bloc->SetDurability(-1);
	bloc->SetIntensity(1.0f);
	AddBlockInfo(bloc);

	// Dirt
	TextureAtlas::TextureIndex dirt = m_atlas->AddTexture(TEXTURE_PATH "dirt.jpg");
	m_atlas->TextureIndexToCoord(dirt, u, v, w, h);
	bloc = new BlockInfo(BTYPE_DIRT, "Dirt", u, v, w, h);
	//bloc->SetDurability(2);
	AddBlockInfo(bloc);

	// Grass
	TextureAtlas::TextureIndex grass = m_atlas->AddTexture(TEXTURE_PATH "grass.jpg");
	TextureAtlas::TextureIndex grassside = m_atlas->AddTexture(TEXTURE_PATH "grassside.jpg");
	m_atlas->TextureIndexToCoord(grass, u, v, w, h);
	m_atlas->TextureIndexToCoord(grassside, cu, cv, cw, ch);
	m_atlas->TextureIndexToCoord(dirt, bu, bv, bw, bh);

	bloc = new BlockInfo(BTYPE_GRASS, "Grass", cu, cv, u, v, bu, bv, w, h);
	bloc->SetDurability(4);
	AddBlockInfo(bloc);

	// Rock
	TextureAtlas::TextureIndex rock = m_atlas->AddTexture(TEXTURE_PATH "rock.jpg");
	m_atlas->TextureIndexToCoord(rock, u, v, w, h);
	bloc = new BlockInfo(BTYPE_ROCK, "Rock", u, v, w, h);
	bloc->SetDurability(4);
	AddBlockInfo(bloc);

	// Water
	TextureAtlas::TextureIndex water = m_atlas->AddTexture(TEXTURE_PATH "water.png");
	m_atlas->TextureIndexToCoord(water, u, v, w, h);
	bloc = new BlockInfo(BTYPE_WATER, "Water", u, v, w, h, true, true);
	bloc->SetDurability(0);
	bloc->SetIntensity(0.8f);
	AddBlockInfo(bloc);

	// Brick
	TextureAtlas::TextureIndex brick = m_atlas->AddTexture(TEXTURE_PATH "brick.jpg");
	m_atlas->TextureIndexToCoord(brick, u, v, w, h);
	bloc = new BlockInfo(BTYPE_BRICK, "Brick", u, v, w, h);
	bloc->SetDurability(3);
	AddBlockInfo(bloc);

	// fromage
	TextureAtlas::TextureIndex fromage = m_atlas->AddTexture(TEXTURE_PATH "fromage.jpg");
	m_atlas->TextureIndexToCoord(fromage, u, v, w, h);
	bloc = new BlockInfo(BTYPE_FROM, "Fromage", u, v, w, h);
	bloc->SetDurability(4);
	AddBlockInfo(bloc);

	//Glass
	TextureAtlas::TextureIndex glass = m_atlas->AddTexture(TEXTURE_PATH "glass.png");
	m_atlas->TextureIndexToCoord(glass,u,v,w,h);
	bloc = new BlockInfo(BTYPE_GLASS,"Glass",u,v,w,h, false, true);
	bloc ->SetDurability(4);
	bloc->SetIntensity(1.f);
	AddBlockInfo(bloc);


	//Bedrock
	TextureAtlas::TextureIndex bedrock = m_atlas->AddTexture(TEXTURE_PATH "bedrock.jpg");
	m_atlas->TextureIndexToCoord(bedrock,u,v,w,h);
	bloc = new BlockInfo(BTYPE_BEDROCK,"Bedrock",u,v,w,h);
	bloc ->SetDurability(-1);
	AddBlockInfo(bloc);

	//leaf
	TextureAtlas::TextureIndex leaf = m_atlas->AddTexture(TEXTURE_PATH "leaf.png");
	m_atlas->TextureIndexToCoord(leaf,u,v,w,h);
	bloc = new BlockInfo(BTYPE_LEAF,"leaf",u,v,w,h,false,true);
	bloc ->SetDurability(4);
	bloc->SetIntensity(0.2f);
	AddBlockInfo(bloc);
	
	//Wood
	TextureAtlas::TextureIndex wood = m_atlas->AddTexture(TEXTURE_PATH "wood.jpg");
	TextureAtlas::TextureIndex woodtop = m_atlas->AddTexture(TEXTURE_PATH "woodtop.jpg");
	m_atlas->TextureIndexToCoord(wood,cu,cv,cw,ch);
	m_atlas->TextureIndexToCoord(woodtop,u,v,w,h);
	bloc = new BlockInfo(BTYPE_WOOD,"wood",cu, cv, u, v, u, v, w, h);
	bloc ->SetDurability(-1);
	AddBlockInfo(bloc);
	//Sand
	TextureAtlas::TextureIndex sand = m_atlas->AddTexture(TEXTURE_PATH "sand.jpg");
	m_atlas->TextureIndexToCoord(sand,u,v,w,h);
	bloc = new BlockInfo(BTYPE_SAND,"sand",u,v,w,h);
	bloc ->SetDurability(4);
	AddBlockInfo(bloc);

	if(!m_atlas->Generate(128, false))
	{
		std::cout << "Unable to generate texture atlas..." << std::endl;
		abort();
	}
}

BlockInfoEncapsuler::~BlockInfoEncapsuler()
{
	for(int i = 0; i < BTYPE_LAST; ++i)
		delete m_types[i];
	delete [] m_types;
	delete m_atlas;
}

void BlockInfoEncapsuler::AddBlockInfo(BlockInfo* bi)
{
	m_types[bi->GetType()] = bi;
}


BlockInfo* BlockInfoEncapsuler::operator[](BlockType type)
{
	return m_types[type];
}


