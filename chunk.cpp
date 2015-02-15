#include "chunk.h"
#include "chunkencapsuler.h"
#include "random.h"
#include "soundmanager.h"


Chunk::Chunk(int posX, int posZ, ChunkEncapsuler* encapsuler) :
		m_blocks(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z), m_isDirty(true), m_posX(
				posX), m_posZ(posZ), m_posChunkX(posX * CHUNK_SIZE_X), m_posChunkZ(
				posZ * CHUNK_SIZE_Z), m_isChanged(false), m_encapsuler(
				encapsuler), m_isLoaded(false),m_blocInfos(BlockInfoEncapsuler::GetInstance()) {
					
}

void Chunk::Load() {
	// On stock les positions dans un string
	std::stringstream sX, sZ;
	sX << m_posX;
	sZ << m_posZ;
	std::string x = sX.str(), z = sZ.str();

#ifdef WIN32
	char path[MAX_PATH];
	SHGetSpecialFolderPath(0, path, CSIDL_APPDATA, 0);
#else
	char path = "";
#endif

	std::string p = std::string(path) + SAVE_CHUNKS_PATH + x + "_" + z + ".bin";

	// On regarde si le chunk existe
	std::ifstream sauvegarde(p.c_str());

	if (!sauvegarde.is_open()) 
	{
		m_blocks.Reset(BTYPE_AIR);
		Perlin m_perlin(16, 6, 1, WORLD_SEED);//Generate different heightmap with different WORLD_SEED

		Random* rnd = Random::GetInstance();

		//Generating blocks in chunk
		for (int x = 0; x < CHUNK_SIZE_X; ++x) 
		{
			for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
				float first = (float) (m_posChunkX + x + 30000) / 2000.f;
				float second = (float) (m_posChunkZ + z + 30000) / 2000.f;
				
				// val = [-1, 1]
				float val = m_perlin.Get(first, second);

				//my = max height
				//my =  [0, 128]
				int my = (int) ((val + 1) * CHUNK_SIZE_Y / 2);

				//Fill all block below 'my' with DIRT or STONE
				for(int y = 1; y <= my - STONE_LEVEL; ++y) {
					m_blocks.Set(x, y, z, BTYPE_ROCK);
				}

				for (int y = my - (STONE_LEVEL + 1); y < my; ++y) {
					m_blocks.Set(x, y, z, BTYPE_DIRT);
				}

				//Set block on top 
				if(my < WATER_LEVEL)
				{
					m_blocks.Set(x, my, z, BTYPE_DIRT);
				}
				else
				{
					m_blocks.Set(x, my, z, BTYPE_GRASS);

					//~10% de chance de creer un arbre
					//TODO: MUST CREATE SOMETHING BETTER THAN THIS WEAK ASS CODE
					if((x+3) <= CHUNK_SIZE_X && (z+3) <= CHUNK_SIZE_Z && (z-3) >= 0 && (x-3) >= 0 && rnd->GetNextAt(m_posChunkX + x, m_posChunkZ + z, 1000) < TREE_GENERATION_RATE)
					{
						AddTree(x,my+1,z);
					}
					
				}

				//IF my is below WATER_LEVEL then put blocks of water 'til WATER_LEVEL
				if(my < WATER_LEVEL) {
					for (int y = my+1; y <= WATER_LEVEL; ++y) {
						m_blocks.Set(x, y, z, BTYPE_WATER);
					}
				}

				//Replace with sand
				if(my >= SAND_MIN_LEVEL) {
					if(my < WATER_LEVEL) {
						for(int i = std::max(SAND_MIN_LEVEL, my - SAND_DEPTH); i <= my; ++i) {
							m_blocks.Set(x, i, z, BTYPE_SAND);
						}
					} else if(my <= SAND_MAX_LEVEL) {
						bool found = false;
						//Check if there is water near of this point
						for(int i = -BEACH_RADIUS; i <= BEACH_RADIUS && !found; ++i) {
							for(int j = -BEACH_RADIUS; j <= BEACH_RADIUS && !found; ++j) {
								float first = (float) (m_posChunkX + x + i + 30000) / 2000.f;
								float second = (float) (m_posChunkZ + z + j + 30000) / 2000.f;

								// val = [-1, 1]
								float val = m_perlin.Get(first, second);

								//my = max height
								//my =  [0, 128]
								int my2 = (int) ((val + 1) * CHUNK_SIZE_Y / 2);

								if(my2 < WATER_LEVEL) {
									for(int k = std::max(SAND_MIN_LEVEL, my - SAND_DEPTH); k <= my; ++k) {
										m_blocks.Set(x, k, z, BTYPE_SAND);
									}
									found = true;
								}
							}
						}
					}
				}

				//Set block at y = 0 to BEDROCK
				m_blocks.Set(x, 0, z, BTYPE_BEDROCK);
		
			}
		}
	} 
	else // On load le fichier du chunk en question
	{
		m_blocks.LoadTo(sauvegarde);
	}
	
	m_isDirty = true;

	Chunk* workingChunk;
	if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX - 1, m_posZ))
			!= NULL)
			workingChunk->m_isDirty = true;
	if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX + 1, m_posZ))
			!= NULL)
			workingChunk->m_isDirty = true;
	if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX, m_posZ - 1))
			!= NULL)
			workingChunk->m_isDirty = true;
	if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX, m_posZ + 1))
			!= NULL)
			workingChunk->m_isDirty = true;

	m_isLoaded = true;

}

//Light related methods
/*
void Chunk::CreateLightmap()
{
	DoFirstPass();
	DoSecondPass();
}

void Chunk::DoFirstPass()
{
	float intensity;
	//First pass: heaven to hell (détermine l'intensité de lumière initial
	for(int x = 0;x < CHUNK_SIZE_X; ++x)
	{
		for(int z = 0; z< CHUNK_SIZE_Z; ++z)
		{
			intensity = 1.0f;
			for(int y = CHUNK_SIZE_Y-1; y >= 0; --y)
			{
				float i = (*m_blocInfos)[m_blocks.Get(x,y,z)]->GetIntensity();
				if(i < intensity)
					intensity = i;
				m_lightmap.Set(x,y,z, intensity);
			}
		}
	}
}

void Chunk::DoSecondPass()
{
	//Second pass: diffusion
	//TODO: checker la valeur de lumière des blocs dans les autres chunks autour du bloc courant si celui-ci se trouve au bord de son chunk
	for(int x = 1;x < CHUNK_SIZE_X-1; ++x)
	{
		for(int y = CHUNK_SIZE_Y-2; y >= 1; --y)
		{
			float intensity = 1.0f;
			for(int z = 1; z < CHUNK_SIZE_Z-1; ++ z)
			{
				if(m_blocks.Get(x,y,z) == BTYPE_AIR)
				{
					float A = m_lightmap.Get(x,y,z);
					float B = 0.0f;

					if(A > 0.25f)
						A *= 0.9f;

					// X + 1
					if(m_blocks.Get(x+1,y,z) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x+1,y,z);
						if(A > B)
							m_lightmap.Set(x+1,y,z,A);
					}
					// X - 1
					if(m_blocks.Get(x-1,y,z) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x-1,y,z);
						if(A > B)
							m_lightmap.Set(x-1,y,z,A);
					}
					// Y + 1
					if(m_blocks.Get(x,y+1,z) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x,y+1,z);
						if(A > B)
							m_lightmap.Set(x,y+1,z,A);
					}
					// Y - 1
					if(m_blocks.Get(x,y-1,z) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x,y-1,z);
						if(A > B)
							m_lightmap.Set(x,y-1,z,A);
					}
					// Z + 1
					if(m_blocks.Get(x,y,z+1) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x,y,z+1);
						if(A > B)
							m_lightmap.Set(x,y,z+1,A);
					}
					// Z - 1
					if(m_blocks.Get(x,y,z-1) == BTYPE_AIR)
					{
						B = m_lightmap.Get(x,y,z-1);
						if(A > B)
							m_lightmap.Set(x,y,z-1,A);
					}

				}
			}
		}
	}
}


//Create Tree at given position


float Chunk::GetLightTest(int x, int y, int z) {
	if (y < 0)
		return 0.0f;
	if (y >= CHUNK_SIZE_Y)
		return 1.0f;

	Chunk* currentChunk = this;
	if (x < 0) {
		currentChunk = m_encapsuler->GetChunkOfPosition(
				currentChunk->m_posX - 1, currentChunk->m_posZ);
		x += CHUNK_SIZE_X;
	} else if (x >= CHUNK_SIZE_X) {
		currentChunk = m_encapsuler->GetChunkOfPosition(
				currentChunk->m_posX + 1, currentChunk->m_posZ);
		x -= CHUNK_SIZE_X;
	} else if (z < 0) {
		currentChunk = m_encapsuler->GetChunkOfPosition(currentChunk->m_posX,
				currentChunk->m_posZ - 1);
		z += CHUNK_SIZE_Z;
	} else if (z >= CHUNK_SIZE_Z) {
		currentChunk = m_encapsuler->GetChunkOfPosition(currentChunk->m_posX,
				currentChunk->m_posZ + 1);
		z -= CHUNK_SIZE_Z;
	}

	return currentChunk->GetLight(x,y,z);
}

float Chunk::GetLight(int x,int y,int z)
{
	return m_lightmap.Get(x,y,z);
}
*/








void Chunk::AddTree(int x, int y, int z)
{
	Random* rnd = Random::GetInstance();
	Random treeRandom(rnd->GetNextAt(m_posChunkX + x, m_posChunkZ + z));

	//Generate width of block of leaves
	int width = 5;
	int minus = width/2;

	//Generate height of trunk
	int randomHeight = treeRandom.GetNext(3) + 2;

	//Generate block of leaves
	for(int iX = 0; iX < width; ++iX)
	{
		for(int iZ = 0; iZ < width; ++iZ)
		{
			for(int iY = 0; iY < width; ++iY)
			{
				int nX = x-minus +iX;
				int nZ = z-minus +iZ;

				if((treeRandom.GetNext(5) > 2))//rand()%2 == 0
					m_blocks.Set(nX ,  y + randomHeight + iY,  nZ , BTYPE_LEAF);
			}
		}
	}

	//Generate trunk
	for(int i = 0; i < randomHeight+(width-1); ++i)
	{
		m_blocks.Set(x,y+i, z, BTYPE_WOOD);
	}

	//Put Leaf Block on top of tree for aesthetic reasons
	m_blocks.Set(x ,  y + randomHeight + width-1,  z , BTYPE_LEAF);
}


Chunk::~Chunk() {
	Save();
}

void Chunk::Save() {
	if (m_isChanged) {
		// On stock les positions dans un string
		std::stringstream sX, sZ;
		sX << m_posX;
		sZ << m_posZ;
		std::string x = sX.str(), z = sZ.str();

		
#ifdef WIN32
	CHAR path[MAX_PATH];
	SHGetSpecialFolderPath(0, path, CSIDL_APPDATA, 0);
#else
	TCHAR path = "";
#endif

	std::string p = std::string(path) + SAVE_CHUNKS_PATH + x + "_" + z + ".bin";
		// On regarde si le chunk existe
		std::ofstream sauvegarde(
			p.c_str());
		m_blocks.SaveTo(sauvegarde);

		m_isChanged = false;
	}
}

void Chunk::RemoveBloc(int x, int y, int z) {
	if(GetBloc(x, y, z) == BTYPE_GLASS)
		SoundManager::GetInstance()->StartSound(SoundManager::GLASS_BREAKING);
	else
	{
		SoundManager::GetInstance()->StartSound(SoundManager::CUBE_BREAKING);
	}

	SetBloc(x, y, z, BTYPE_AIR);
}

void Chunk::SetBloc(int x, int y, int z, BlockType type) {
	BlockType lastType = Get(x, y, z);

	if(type == lastType || lastType == BTYPE_BEDROCK)
		return;

	m_isDirty = true;
	m_isChanged = true;

	m_blocks.Set(x, y, z, type);

	Chunk* workingChunk;

	if (x <= 0) {
		if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX - 1,
				m_posZ)) != NULL)
				workingChunk->Update(true);
	} else if (x >= CHUNK_SIZE_X - 1) {
		if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX + 1,
				m_posZ)) != NULL)
				workingChunk->Update(true);
	}
	if (z <= 0) {
		if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX,
				m_posZ - 1)) != NULL)
				workingChunk->Update(true);
	} else if (z >= CHUNK_SIZE_Z - 1) {
		if ((workingChunk = m_encapsuler->GetChunkOfPosition(m_posX,
				m_posZ + 1)) != NULL)
				workingChunk->Update(true);
	}
}

int Chunk::GetMaxY(int cx, int cz, BlockType& bloc)
{
	//On scanne pour trouver la première position valide en Y.
	for(int cy = CHUNK_SIZE_Y - 1; cy >= 0; --cy)
	{
		BlockInfo* bi = (*m_blocInfos)[GetBlocTest(cx, cy, cz)];

		if(!bi->IsWalkable())
		{
			bloc = (*m_blocInfos)[GetBlocTest(cx, cy-1, cz)]->GetType();
			return cy + 1;
		}
	}

	return -1;
}

BlockType Chunk::GetBloc(int x, int y, int z) {
	if(!m_isLoaded)
		return BTYPE_AIR;
	if(x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z)
		return BTYPE_AIR;
	return m_blocks.Get(x, y, z);
}

// Pour l'optimisation des vertex, on test les cube autour en testant les limites du chunk
BlockType Chunk::GetBlocTest(int x, int y, int z) {
	if(!m_isLoaded)
		return BTYPE_AIR;

	if (y < 0)
		return BTYPE_ROCK;
	if (y >= CHUNK_SIZE_Y)
		return BTYPE_ROCK;

	Chunk* currentChunk = this;
	if (x < 0) {
		currentChunk = m_encapsuler->GetChunkOfPosition(
				currentChunk->m_posX - 1, currentChunk->m_posZ);
		x += CHUNK_SIZE_X;
	} else if (x >= CHUNK_SIZE_X) {
		currentChunk = m_encapsuler->GetChunkOfPosition(
				currentChunk->m_posX + 1, currentChunk->m_posZ);
		x -= CHUNK_SIZE_X;
	} else if (z < 0) {
		currentChunk = m_encapsuler->GetChunkOfPosition(currentChunk->m_posX,
				currentChunk->m_posZ - 1);
		z += CHUNK_SIZE_Z;
	} else if (z >= CHUNK_SIZE_Z) {
		currentChunk = m_encapsuler->GetChunkOfPosition(currentChunk->m_posX,
				currentChunk->m_posZ + 1);
		z -= CHUNK_SIZE_Z;
	}

	if (currentChunk == NULL || !currentChunk->m_isLoaded)
		return BTYPE_ROCK;
	return currentChunk->Get(x, y, z);
}

BlockType Chunk::Get(int x, int y, int z) const {
	return m_blocks.Get(x, y, z);
}

void Chunk::Update(bool force) {
	if (m_isDirty || force) {


		ChunkMesh::VertexData* vd = new ChunkMesh::VertexData[MAX_VERTEX_BY_CHUNK];
		ChunkMesh::VertexData* vtransparent = new ChunkMesh::VertexData[MAX_VERTEX_BY_CHUNK];

		int count = 0;
		int countTransparent = 0;

		for (int x = 0; x < CHUNK_SIZE_X; ++x) {
			for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
				for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
					if (count >= MAX_VERTEX_BY_CHUNK)
						break;

					BlockInfo* bi = (*m_blocInfos)[GetBlocTest(x, y, z)];

					if (bi->GetType() != BTYPE_AIR) {
						if(bi->IsTransparent())
							AddBlockToMesh(vtransparent, countTransparent, bi, x, y, z);
						else
							AddBlockToMesh(vd, count, bi, x, y, z);
					}
				}
			}
		}
		if (count >= MAX_VERTEX_BY_CHUNK) {
			count = MAX_VERTEX_BY_CHUNK;
			std::cout
					<< "[ Chunk :: Update ] Chunk data truncaned, too much vertices to have a 16 bit index "
					<< std::endl;
		}

		m_chunkMesh.SetMeshData(vd, count);
		m_transparentMesh.SetMeshData(vtransparent, countTransparent);
		delete[] vd;
		delete[] vtransparent;

		m_isDirty = false;
	}
}
	
void Chunk::AddBlockToMesh(ChunkMesh::VertexData* vd, int& count, const BlockInfo* type,
		int x, int y, int z) {

		float uc = type->GetUC();
		float vc = type->GetVC();
		float uu = type->GetUU();
		float vu = type->GetVU();
		float ub = type->GetUB();
		float vb = type->GetVB();

		float w = type->GetW();

		float intensity = 1.0f;
		
		//TODO: aller cherche la valeur de lumière d'un bloc d'un autre chunk dans le lightmap de celui-ci
		//si le bloc courant est au bord de son chunk

		BlockType bloc = GetBlocTest(x, y, z + 1);
		// front
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc + w, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc + w, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc + w);
		}

		bloc = GetBlocTest(x, y, z - 1);

		// back
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc);
		}

		bloc = GetBlocTest(x + 1, y, z);
		intensity = 0.5f;
		// right
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc + w);
		}

		bloc = GetBlocTest(x - 1, y, z);
		

		// left
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, uc, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uc + w, vc);
		}
		

		bloc = GetBlocTest(x, y + 1, z);
		intensity = 0.7f;
		// top
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ + .5f, (intensity),(intensity), (intensity), uu, vu);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uu + w, vu);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, uu + w, vu + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y + .5f,
					z + m_posChunkZ + .5f, (intensity), (intensity), (intensity), uu, vu + w);
		}
		
		bloc = GetBlocTest(x, y - 1, z);
		
		// bottom
		if (bloc != type->GetType() && (*m_blocInfos)[bloc]->IsTransparent()) {
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, ub, vb);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ + .5f, intensity, intensity, intensity, ub + w, vb);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX - .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, ub + w, vb + w);
			vd[count++] = ChunkMesh::VertexData(x + m_posChunkX + .5f, y - .5f,
					z + m_posChunkZ - .5f, intensity, intensity, intensity, ub, vb + w);
		}
}

void Chunk::Render() {
	if (!m_isLoaded) {
		return;
	}
	m_chunkMesh.Render();
}

void Chunk::RenderTransparent() {
	if (!m_isLoaded) {
		return;
	}
	m_transparentMesh.Render();
}

bool Chunk::IsDirty() const {
	return m_isDirty;
}

int Chunk::GetX() {
	return m_posX;
}

int Chunk::GetZ() {
	return m_posZ;
}

bool Chunk::IsLoaded() const {
	return m_isLoaded;
}
