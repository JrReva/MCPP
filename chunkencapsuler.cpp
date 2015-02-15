#include "chunkencapsuler.h"
#include "preferences.h"

void ChunkEncapsuler::Resize() {
	Array2d<Chunk*>* newArray = new Array2d<Chunk*>(Preferences::GetLoadDistance() * 2 / CHUNK_SIZE_X, Preferences::GetLoadDistance() * 2 / CHUNK_SIZE_Z);

	int delta = (newArray->GetSizeX() - m_array->GetSizeX()) / 2;
	int center = newArray->GetSizeX() / 2;
	int lastCenter = m_array->GetSizeX() / 2;

	Chunk* centerChunk = m_array->Get(m_array->GetSizeX() / 2, m_array->GetSizeY() / 2);
	
	int centerX = centerChunk->GetX();
	int centerY = centerChunk->GetZ();

	int startX = centerX - (Preferences::GetLoadDistance() / CHUNK_SIZE_X);
	int startY = centerY - (Preferences::GetLoadDistance() / CHUNK_SIZE_Z);

	for(int i = 0; i < newArray->GetSizeX(); ++i) {
		for(int j = 0; j < newArray->GetSizeY(); ++j) {
			if(delta < 0 || (center - i <= delta && center - i > -delta && abs(center - j) <= delta && center - j > -delta)) {
				newArray->Set(i, j, m_array->Get(lastCenter + (i - center), lastCenter + (j - center)));
			} else {
				newArray->Set(i, j, new Chunk(startX + i, startY + j, this));
			}
		}
	}

	if(delta < 0) {
		int rdelta = lastCenter + delta;

		for(int i = 0; i < m_array->GetSizeX(); ++i) {
			for(int j = 0; j < m_array->GetSizeY(); ++j) {

				if(i < lastCenter - rdelta || j < lastCenter - rdelta || i >= lastCenter + rdelta || j >= lastCenter + rdelta)
					delete (m_array->Get(i, j));
			}
		}
	}
	
	delete m_array;

	m_array = newArray;
}

ChunkEncapsuler::ChunkEncapsuler() {
	m_array = new Array2d<Chunk*>(Preferences::GetLoadDistance() * 2 / CHUNK_SIZE_X,
			Preferences::GetLoadDistance() * 2 / CHUNK_SIZE_Z);
}

ChunkEncapsuler::~ChunkEncapsuler() {
	m_array->FreeMemory();
	delete m_array;
}

void ChunkEncapsuler::LoadResource() {
	int startX = (WORLD_CENTER - Preferences::GetLoadDistance()) / CHUNK_SIZE_X;
	int startY = (WORLD_CENTER - Preferences::GetLoadDistance()) / CHUNK_SIZE_Z;

	for (int x = 0; x < m_array->GetSizeX(); ++x) {
		for (int y = 0; y < m_array->GetSizeY(); ++y) {
			m_array->Set(x, y, new Chunk(startX + x, startY + y, this));
		}
	}
}

void ChunkEncapsuler::SaveAll() {
	for (int x = 0; x < m_array->GetSizeX(); ++x) {
		for (int y = 0; y < m_array->GetSizeY(); ++y) {
			m_array->Get(x, y)->Save();
		}
	}
}

Chunk* ChunkEncapsuler::GetChunkOfPosition(int x, int y) const {
	Chunk* firstChunk = m_array->Get(0, 0);

	int deltaX = x - firstChunk->GetX();
	int deltaY = y - firstChunk->GetZ();

	if (deltaX < 0 || deltaY < 0 || deltaX >= m_array->GetSizeX()
			|| deltaY >= m_array->GetSizeY())
		return NULL;

	return m_array->Get(deltaX, deltaY);
}

Chunk* ChunkEncapsuler::GetChunkOfPoint(int x, int y, int* cx, int* cy) const {
	*cx = x % CHUNK_SIZE_X;
	*cy = y % CHUNK_SIZE_Z;

	int chunkX = x / CHUNK_SIZE_X;
	int chunkY = y / CHUNK_SIZE_Z;

	if(*cx < 0) {
		(*cx) += CHUNK_SIZE_X;
	}
	if(*cy < 0) {
		(*cy) += CHUNK_SIZE_Z;
	}

	if(x < 0 && *cx != 0) {
		--chunkX;
	}
	if(y < 0 && *cy != 0) {
		--chunkY;
	}

	return GetChunkOfPosition(chunkX, chunkY);
}

Chunk* ChunkEncapsuler::GetChunkOfPoint(int x, int y) const {
	int cx, cy;
	return GetChunkOfPoint(x, y, &cx, &cy);
}

void ChunkEncapsuler::SetPlayer2DPosition(int x, int y) {
	maxViewX = (x + Preferences::GetViewDistance()) / CHUNK_SIZE_X;
	maxViewY = (y + Preferences::GetViewDistance()) / CHUNK_SIZE_Z;

	minViewX = (x - Preferences::GetViewDistance()) / CHUNK_SIZE_X;
	minViewY = (y - Preferences::GetViewDistance()) / CHUNK_SIZE_Z;

	Chunk* middleChunk = m_array->Get(m_array->GetSizeX() / 2,
		m_array->GetSizeY() / 2);

	Deplace((x / CHUNK_SIZE_X) - middleChunk->GetX(),
			(y / CHUNK_SIZE_Z) - middleChunk->GetZ());
}

void ChunkEncapsuler::RenderSolid(float elapsedTime, bool render) {
	static float chunkLoaderCounter = SECOND_BY_CHUNK_LOAD;
	static float chunkUpdateCounter = SECOND_BY_CHUNK_UPDATE;
	int loadNumber = 0;
	int updateNumber = 0;

	if(render) {
		chunkLoaderCounter -= elapsedTime;
		chunkUpdateCounter -= elapsedTime;

		while (chunkLoaderCounter < 0) {
			chunkLoaderCounter += SECOND_BY_CHUNK_LOAD;
			++loadNumber;
		}

		while (chunkUpdateCounter < 0) {
			chunkUpdateCounter += SECOND_BY_CHUNK_UPDATE;
			++updateNumber;
		}
	} else {
		loadNumber = 3;
		updateNumber = 3;
	}

	int sizeX = m_array->GetSizeX();
	int middle = (sizeX / 2) - 1;
	int i, j;

	for (i = 0; i <= middle; ++i) {
		if (i != 0)
			for (j = 0; j <= (i * 2); ++j)
				Update(m_array->Get(middle + i - j, middle - i), updateNumber, loadNumber, render);

		for (j = 0; j <= (i * 2); ++j)
			Update(m_array->Get(middle - i, middle - i + j), updateNumber, loadNumber, render);

		for (j = 0; j <= (i * 2); ++j)
			Update(m_array->Get(middle - i + j, middle + i + 1), updateNumber, loadNumber, render);

		for (j = 0; j <= (i * 2) + 1; ++j)
			Update(m_array->Get(middle + i + 1, middle + i + 1 - j), updateNumber, loadNumber, render);
	}

	if (sizeX % 2) {
		for (int i = 0; i < sizeX; ++i)
			Update(m_array->Get(i, sizeX), updateNumber, loadNumber, render);
		for (int i = 1; i < sizeX; ++i)
			Update(m_array->Get(sizeX, i), updateNumber, loadNumber, render);
	}
}
void ChunkEncapsuler::RenderTransparent() {
	int sizeX = m_array->GetSizeX();
	int middle = (sizeX / 2) - 1;
	int i, j;
	if (sizeX % 2) {
		for (int i = sizeX - 1; i >= 0; --i) {
			UpdateTransparent(m_array->Get(i, sizeX));
		}
		for (int i = 1; i < sizeX; ++i){
			UpdateTransparent(m_array->Get(sizeX, i));
		}
	}

	for (i = middle; i >= 0; --i) {
		if (i != 0)
			for (j = (i * 2); j >= 0; --j)
				UpdateTransparent(m_array->Get(middle + i - j, middle - i));

		for (j = (i * 2); j >= 0; --j)
			UpdateTransparent(m_array->Get(middle - i, middle - i + j));

		for (j = (i * 2); j >= 0; --j)
			UpdateTransparent(m_array->Get(middle - i + j, middle + i + 1));

		for (j = (i * 2) + 1; j >= 0; --j)
			UpdateTransparent(m_array->Get(middle + i + 1, middle + i + 1 - j));
	}
}

void ChunkEncapsuler::Render(float elapsedTime, bool render) {
	RenderSolid(elapsedTime, render);

	if(render) {
		RenderTransparent();
	}
}

void ChunkEncapsuler::UpdateTransparent(Chunk* chunk) {
	if(chunk->GetX() >= minViewX && chunk->GetX() <= maxViewX && chunk->GetZ() >= minViewY && chunk->GetZ() <= maxViewY)
		chunk->RenderTransparent();
}

void ChunkEncapsuler::Update(Chunk* chunk, int& updateNumber, int& loadNumber, bool render) {
	if(!chunk->IsLoaded()) {
		if(loadNumber <= 0)
			return;
		else {
			chunk->Load();
			--loadNumber;
		}
	}

	if(updateNumber > 0 && chunk->IsDirty()) {
		chunk->Update();
		--updateNumber;
	}

	if(!render)
		return;

	if(chunk->GetX() < minViewX || chunk->GetX() > maxViewX || chunk->GetZ() < minViewY || chunk->GetZ() > maxViewY)
		return;

	chunk->Render();
}

void ChunkEncapsuler::Deplace(int deltaX, int deltaY) {
	if (deltaX > 0) {
		for (int x = 0; x < m_array->GetSizeX(); ++x) {
			for (int y = 0; y < m_array->GetSizeY(); ++y) {
				if (x < deltaX)
					delete m_array->Get(x, y);

				if (x < m_array->GetSizeX() - deltaX)
					m_array->Set(x, y, m_array->Get(x + deltaX, y));
				else {
					Chunk* lastChunk = m_array->Get(x - 1, y);
					m_array->Set(
							x,
							y,
							new Chunk(lastChunk->GetX() + 1, lastChunk->GetZ(),
									this));
				}
			}
		}
	} else if (deltaX < 0) {
		for (int x = m_array->GetSizeX() - 1; x >= 0; --x) {
			for (int y = 0; y < m_array->GetSizeY(); ++y) {
				if (x > m_array->GetSizeX() + deltaX)
					delete m_array->Get(x, y);

				if (x > -deltaX - 1)
					m_array->Set(x, y, m_array->Get(x + deltaX, y));
				else {
					Chunk* lastChunk = m_array->Get(x + 1, y);
					m_array->Set(
							x,
							y,
							new Chunk(lastChunk->GetX() - 1, lastChunk->GetZ(),
									this));
				}
			}
		}
	}

	if (deltaY > 0) {
		for (int y = 0; y < m_array->GetSizeY(); ++y) {
			for (int x = 0; x < m_array->GetSizeX(); ++x) {
				if (y < deltaY)
					delete m_array->Get(x, y);

				if (y < m_array->GetSizeY() - deltaY)
					m_array->Set(x, y, m_array->Get(x, y + deltaY));
				else {
					Chunk* lastChunk = m_array->Get(x, y - 1);
					m_array->Set(
							x,
							y,
							new Chunk(lastChunk->GetX(), lastChunk->GetZ() + 1,
									this));
				}
			}
		}
	} else if (deltaY < 0) {
		for (int y = m_array->GetSizeY() - 1; y >= 0; --y) {
			for (int x = 0; x < m_array->GetSizeX(); ++x) {
				if (y > m_array->GetSizeY() + deltaY)
					delete m_array->Get(x, y);

				if (y > -deltaY - 1)
					m_array->Set(x, y, m_array->Get(x, y + deltaY));
				else {
					Chunk* lastChunk = m_array->Get(x, y + 1);
					m_array->Set(
							x,
							y,
							new Chunk(lastChunk->GetX(), lastChunk->GetZ() - 1,
									this));
				}
			}
		}
	}
}
