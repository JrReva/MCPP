#include "scaredaistate.h"
#include "mob.h"

ScaredAIState::ScaredAIState(Mob* mob, MovableEntity* target)
	: AIState(mob, target)
{
}

//Point d'entr�e de l'IA.
void ScaredAIState::Update(const float& elapsedTime)
{
	
}