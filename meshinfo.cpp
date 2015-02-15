#include "meshinfo.h"

MeshInfo::MeshInfo(float* vert, const float& nbData, const float& nbVert, const float& scale, const std::string texturePath)
{
	ChunkMesh::VertexData* vd = ChunkMesh::ParseVerts(vert, nbData, nbVert, _width, _height, m_offset ,scale);

	m_mesh = new ChunkMesh();
	m_mesh->SetMeshData(vd, nbVert);
	m_texture = new Texture();
	m_texture->Load(texturePath.c_str());

	delete[] vd;
}

MeshInfo::~MeshInfo()
{
	//On libère les ressources dès que le MeshInfo est libéré.
	if(m_texture != NULL)
		delete m_texture;
	if(m_mesh != NULL)
		delete m_mesh;
}

void MeshInfo::Render()
{
	if(m_texture->IsValid() && m_mesh->IsValid())
	{
		m_texture->Bind();
		m_mesh->Render();
	}
}