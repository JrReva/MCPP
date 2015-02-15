//===========================================================
//Auteur : Gabriel Lemire
//Date de création : 21 février 2012
//Description : Représente un Mob de type Fatso.
//============================================================
#ifndef FATSO_H__
#define FATSO_H__

#define FATSO_JUMP				2.f
#define FATSO_DETECT_RADIUS		35.f
#define FATSO_LIFE				30
#define FATSO_SPEED				1.5f
#define FATSO_DAMAGE			3

#include "mob.h"
#include "aggressiveaistate.h"
#include "passiveaistate.h"
#include "meshinfo.h"
#include "player.h"

class Fatso : public Mob
{
	//Constructeurs et destructeur
public :
	Fatso(float posX, float posY, float posZ, Player* player, MeshInfo* mesh);
	virtual ~Fatso() { }

public :
	virtual void Update(float elapsedTime);
	void virtual GetAttacked(MovableEntity* attacker, const int& damage);
};

#endif