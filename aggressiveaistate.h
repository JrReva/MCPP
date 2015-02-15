#ifndef AGRESSIVE_AI_STATE_H__
#define AGRESSIVE_AI_STATE_H__

#include "aistate.h"
#include "movableentity.h"

class Mob;

class AgressiveAIState : public AIState
{
public :
	AgressiveAIState(Mob* mob, MovableEntity* target);

public:
	virtual void Update(const float& elapsedTime);
};

#endif