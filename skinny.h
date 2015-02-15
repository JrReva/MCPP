//===========================================================
//Auteur : Gabriel Lemire
//Date de création : 18 février 2012
//Description : Représente un Mob de type Skinny.
//===========================================================

#ifndef SKINNY_H__
#define SKINNY_H__

#define SKINNY_JUMP					6.8f
#define SKINNY_DETECT_RADIUS		20.f
#define SKINNY_LIFE					10
#define SKINNY_SPEED				2.5f
#define SKINNY_DAMAGE				1

#include "mob.h"
#include "passiveaistate.h"
#include "scaredaistate.h"
#include "meshinfo.h"
#include "player.h"

class Skinny : public Mob
{
//Constructeur(s) et destructeur...
public :
	Skinny(float posX, float posY, float posZ, Player* player, MeshInfo* mesh);
	virtual ~Skinny() { }

public :
	void virtual Update(float elapsedTime);
	void virtual GetAttacked(MovableEntity* attacker, const int& damage);
};

#endif