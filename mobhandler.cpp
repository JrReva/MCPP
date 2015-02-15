#include "mobhandler.h"
#include "engine.h"
#include "preferences.h"
#include "chunk.h"
#include "chunkencapsuler.h"
#include "define.h"
#include "blockinfoencapsuler.h"

//Inclusion de meshs.
#include "media/mesh/skinnymesh.h"
#include "media/mesh/fatso.h"
#include "media/mesh/piggy.h"

MobHandler::MobHandler(Player* player)
	:m_nbMesh(0), m_cleanupET(0), m_autospawnET(Preferences::GetMobSpawnTime() - 2.f)
{
	m_player = player;
	m_nbMesh = 3;
	m_meshes = new MeshInfo*[m_nbMesh];

	//Chargement des MeshInfo à l'avance.
	m_meshes[0] = new MeshInfo(skinnyVerts, skinnyNbData, skinnyNbVerts, 0.3f, TEXTURE_PATH "skinny.png");
	m_meshes[1] = new MeshInfo(fatsoVerts, fatsoNbData, fatsoNbVerts, 0.5f, TEXTURE_PATH "fatso.png");
	m_meshes[2] = new MeshInfo(piggyVerts, piggyNbData, piggyNbVerts, 0.3f, TEXTURE_PATH "piggy.png");

	m_mobs = new MobList();
}

MobHandler::~MobHandler()
{
	//Destruction des MeshInfo.
	for(int i = 0; i < m_nbMesh; ++i)
	{
		delete m_meshes[i];
	}

	delete[] m_meshes;

	//Destruction des mobs.
	for(MobList::iterator it = m_mobs->begin(); it != m_mobs->end(); ++it)
	{
		if(*it != NULL)
			delete *it;
	}

	
}

void MobHandler::SpawnMob(MobType type, float x, float y, float z)
{

	std::cout << "Spawning ";
	Mob* mob;

	switch(type)
	{
		case SKINNY:
			mob = new Skinny(x, y, z, m_player, m_meshes[0]);
			std::cout << "SKINNY ";
			break;

		case FATSO:
			mob = new Fatso(x, y, z, m_player, m_meshes[1]);
			std::cout << "FATSO ";
			break;

		case PIGGY:
			mob = new Piggy(x, y, z, m_player, m_meshes[2]);
			std::cout << "PIGGY ";
			break;
	}

	std::cout << "at point ["<< x <<", "<< y <<", "<< z <<"]" << std::endl;

	//On accepte de mettre le mob dans le render seulement s'il est à l'intérieur des
	//limites de disposition.
	if(mob->Calculate2DDistance(m_player) >= Preferences::GetMobDisposeDistance())
		delete mob;
	else
		m_mobs->push_back(mob);
}

void MobHandler::Update(float elapsedTime)
{
	bool cleanup = (m_cleanupET += elapsedTime) >= MOBS_CLEANUP_DELAY;
	std::vector<Mob*> mobsToRemove;

	bool autospawn = (m_autospawnET += elapsedTime) >= Preferences::GetMobSpawnTime();

	//On parcourt les mobs.
	for(MobList::iterator it = m_mobs->begin(); it != m_mobs->end(); it++)
	{
		Mob* mob = *it;

		//On s'occupe du mob s'il n'est pas mort.
		if(!mob->IsDead())
		{
			mob->Update(elapsedTime);			//On passe le contrôle à l'IA.
			mob->MoveSimulation(elapsedTime);	//On simule le mouvement du mob.

			if(!mob->GetDispose()) {

			//On vérifie les collisions.
			Engine::GetInstance()->Collision(mob);

			//On ne render que si nécessaire.
			if(mob->GetIsRendering())
 				mob->Render();
			}
		}

		//Si on décide de faire un nettoyage et que le mob courant s'y prête...
		if(cleanup && mob->IsDead() || mob->GetDispose())
			mobsToRemove.push_back(mob);
	}

	if(cleanup && mobsToRemove.size() != 0)
		Cleanup(mobsToRemove);

	if(autospawn)
		AutoSpawn();
}

void MobHandler::Cleanup(const std::vector<Mob*>& toClean)
{
	for(int i = 0; i < toClean.size(); ++i)
	{
		m_mobs->remove(toClean[i]);
	}

	m_cleanupET = 0;
}

void MobHandler::AutoSpawn()
{
	Random* rand = Random::GetInstance();

	int counter = 0;
	int amountMob = rand->GetNext(5);	//On spawn un maximum de 5 mobs a chaque update.

	//On tente de faire spawner des mobs si le nombre maximal n'est pas atteint
	//, mais aussi si ça fait moins de 11 fois que l'on échoue.
	while(m_mobs->size() < Preferences::GetMaxMob() && counter < 10 && amountMob > 0)
	{
		
		float x = rand->GetNextFloat(m_player->Position().x - Preferences::GetMobDisposeDistance(), m_player->Position().x + Preferences::GetMobRenderDistance());
		float z = rand->GetNextFloat(m_player->Position().z - Preferences::GetMobDisposeDistance(), m_player->Position().z + Preferences::GetMobRenderDistance());

		Engine* e = Engine::GetInstance();
		ChunkEncapsuler* world = e->GetChunks();

		int cx = 0.f, cz = 0.f;
		Chunk* c = world->GetChunkOfPoint(x, z, &cx, &cz);

		if(c != 0) {
			BlockType bt;
			int y = c->GetMaxY(cx, cz, bt);

			//On spawn seulement si on est pas dans l'eau
			if(y > 0 && bt != BTYPE_WATER)
			{
				int proba = rand->GetNext(100);
				SpawnMob(Preferences::GetMobType(proba), x, y, z);
				counter = 0;
				--amountMob;
			}
		}

		++counter;
	}
}