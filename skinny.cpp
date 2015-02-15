#include "skinny.h"
#include "soundmanager.h"

Skinny::Skinny(float posX, float posY, float posZ, Player* player, MeshInfo* mesh)
	:Mob(posX, posY, posZ, 0.f,0.f, SKINNY_JUMP, SKINNY_DETECT_RADIUS, SKINNY_LIFE,
	SKINNY_SPEED, new PassiveAIState(this), player, SKINNY_DAMAGE, mesh)
{
}

void Skinny::Update(float elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void Skinny::GetAttacked(MovableEntity* attacker, const int& damage)
{
	SoundManager::GetInstance()->SKINNY_HURT;
}