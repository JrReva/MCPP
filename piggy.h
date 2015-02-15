//===========================================================
//Auteur : Gabriel Lemire
//Date de création : 18 février 2012
//Description : Représente un Mob de type Piggy.
//===========================================================
#ifndef PIGGY_H__
#define PIGGY_H__

#define PIGGY_JUMP				5.f
#define PIGGY_DETECT_RADIUS		30.f
#define PIGGY_LIFE				5
#define PIGGY_SPEED				2.5f
#define PIGGY_DAMAGE			0.f

#include "mob.h"
#include "passiveaistate.h"
#include "scaredaistate.h"
#include "meshinfo.h"
#include "player.h"

class Piggy : public Mob
{
public :
	Piggy(float posX, float posY, float posZ, Player* player, MeshInfo* mesh);
	virtual ~Piggy() { }

public :
	void virtual Update(float elapsedTime);
	virtual void GetAttacked(MovableEntity* attacker, const int& damage);
};

#endif