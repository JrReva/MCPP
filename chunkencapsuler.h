#ifndef CHUNKENCAPSULER_H__
#define CHUNKENCAPSULER_H__

#include "define.h"
#include "array2d.h"
#include "chunk.h"
#include "vector3.h"
#include "blockinfoencapsuler.h"
#include "blockinfo.h"

class ChunkEncapsuler {
public:
	ChunkEncapsuler();
	~ChunkEncapsuler();
	void LoadResource();
	void SetPlayer2DPosition(int x, int y);
	Chunk* GetChunkOfPosition(int x, int y) const;
	Chunk* GetChunkOfPoint(int x, int y, int* cx, int* cy) const;
	Chunk* GetChunkOfPoint(int x, int y) const;
	void Render(float elapsedTime, bool render = true);
	void SaveAll();
	void Resize();
private:
	void Update(Chunk* chunk, int& updateNumber, int& loadNumber, bool render);
	void UpdateTransparent(Chunk* chunk);
	void Deplace(int deltaX, int deltaY);
	void RenderTransparent();
	void RenderSolid(float elapsedTime, bool render);
	Array2d<Chunk*>* m_array;
	
	int maxViewX;
	int maxViewY;
	int minViewX;
	int minViewY;
};


#endif
