#ifndef SCARED_AI_STATE_H__
#define SCARED_AI_STATE_H__

#include "aistate.h"
#include "movableentity.h"

class Mob;

class ScaredAIState : public AIState
{
public :
	ScaredAIState(Mob* mob, MovableEntity* target);

public:
	virtual void Update(const float& elapsedTime);
};

#endif