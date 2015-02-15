#include "piggy.h"
#include "soundmanager.h"

Piggy::Piggy(float posX, float posY, float posZ, Player* player, MeshInfo* mesh)
	:Mob(posX, posY, posZ, 0.f, 0.f, PIGGY_JUMP, PIGGY_DETECT_RADIUS, PIGGY_LIFE,
	PIGGY_SPEED, new PassiveAIState(this), player, PIGGY_DAMAGE, mesh)
{
}

void Piggy::Update(float elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void Piggy::GetAttacked(MovableEntity* attacker, const int& damage)
{
	SoundManager::GetInstance()->PIGGY_HURT;
}