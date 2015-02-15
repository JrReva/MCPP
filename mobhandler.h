//=========================================================================
//Auteur : Gabriel Lemire
//Date de création : 21 février 2012
//Description : Charge en mémoire les mesh et les textures des Mobs. Se
//	charge également de générer des mobs à la demande.
//=========================================================================
#ifndef MOBHANDLER_H__
#define MOBHANDLER_H__

#include <list>
#include <vector>
#include "meshinfo.h"
#include "skinny.h"
#include "mob.h"
#include "define.h"
#include "fatso.h"
#include "piggy.h"


enum MobType { SKINNY, FATSO, PIGGY };
typedef std::list<Mob*> MobList;

class MobHandler
{
public :
	MobHandler(Player* player);
	virtual ~MobHandler();

public :
	void SpawnMob(MobType type, float x, float y, float z);
	void Update(float elapsedTime);
	void ForceCleanup();

private :
	bool IsDisposable(const Mob*& mob) const { return mob->IsDead() || mob->GetDispose(); }
	void Cleanup(const std::vector<Mob*>& toClean);
	void AutoSpawn();

private :
	Player* m_player;
	int m_nbMesh;
	MeshInfo** m_meshes;	//tableau de pointeurs de MeshInfo.
	float m_cleanupET;
	float m_autospawnET;

	MobList* m_mobs;
};

#endif