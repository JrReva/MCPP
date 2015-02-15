#ifndef MESHINFO_H__
#define MESHINFO_H__

#include <string>
#include "chunkmesh.h"
#include "texture.h"
#include "vector3.h"

class MeshInfo
{
public :
	MeshInfo(float* vert, const float& nbData, const float& nbVert, const float& scale, const std::string texturePath);
	virtual ~MeshInfo();

public :
	void Render();

public :
	float GetHeight() const { return _height; }
	float GetWidth() const { return _width; }
	Vector3f GetOffset() const { return m_offset; }

	ChunkMesh* GetMesh() const { return m_mesh; }
	Texture* GetTexture() const { return m_texture; }

private :
	ChunkMesh* m_mesh;
	Texture* m_texture;
	float _height, _width;
	Vector3f m_offset;
};

#endif