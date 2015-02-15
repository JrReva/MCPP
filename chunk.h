#ifndef CHUNK_H__
#define CHUNK_H__

#include <sstream>
#include "define.h"
#include "array3d.h"
#include "chunkmesh.h"
#include "blockinfo.h"
#include "blockinfoencapsuler.h"
#include "perlin.h"

class ChunkEncapsuler;

class Chunk
{
public:
    Chunk(int x, int z, ChunkEncapsuler* encapsuler);
    ~Chunk();

    void RemoveBloc(int x, int y, int z);
    void SetBloc(int x, int y, int z, BlockType type);
    BlockType GetBloc(int x, int y, int z);
	BlockType GetBlocTest(int x, int y, int z);
	//float GetLightTest(int x, int y, int z);
	//float GetLight(int x, int y, int z);

	void Update(bool force = false);
	void Render();
	void RenderTransparent();
	void Save();
	bool IsDirty() const;
	void AddBlockToMesh(ChunkMesh::VertexData*vd, int& count, const BlockInfo* type, int x, int y, int z);

	BlockType Get(int x, int y, int z) const;
	int GetX();
	int GetZ();
	bool IsLoaded() const;
	void Load();

	int GetMaxY(int x, int z, BlockType& bloc);
private:
	//void CreateLightmap();
	//void DoFirstPass();
	//void DoSecondPass();


	void AddTree(int x, int y, int z);
	int SimpleRandom(int lim);
	bool m_isLoaded;
	bool m_isDirty, m_isChanged;
	float m_u, m_v, m_w, m_h;
	int m_posX, m_posZ;
	int m_posChunkX, m_posChunkZ;
	std::string m_nomBin;

	//Array3d<float> m_lightmap;
	Array3d<BlockType> m_blocks;
	ChunkMesh m_chunkMesh;
	ChunkMesh m_transparentMesh;
	std::fstream m_fichier;
	ChunkEncapsuler* m_encapsuler;
	BlockInfoEncapsuler* m_blocInfos;
};

#endif // CHUNK_H__
