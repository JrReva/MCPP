#ifndef PASSIVE_AI_STATE_H__
#define PASSIVE_AI_STATE_H__

#include "aistate.h"

class Mob;

class PassiveAIState : public AIState
{
public :
	PassiveAIState(Mob* mob);

public:
	virtual void Update(const float& elapsedTime);

private :
	Random* m_rand;
	float m_actionTime;
	float m_rotX;
	bool m_moving;
};

#endif