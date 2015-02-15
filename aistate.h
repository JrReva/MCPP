#ifndef AISTATE_H__
#define AISTATE_H__

#include "movableentity.h"
#include "player.h"

class Mob;

class AIState
{
//Constructeur(s) et destructeur...
public :
	AIState(Mob* mob, MovableEntity* target = NULL);
	virtual ~AIState() { }

//Méthodes publiques virtuelles pures...
public :
	virtual void Update(const float& elapsedTime) = 0;

//Accesseurs...
public :
	void SetTarget(MovableEntity* target);

//Champs protected...
protected :
	Mob* m_mob;
	MovableEntity* m_target;
	int _lastActionTime, _tick;

protected :
	float FindAngleWithTarget() const;
};

#endif