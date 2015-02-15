#include "fatso.h"
#include "soundmanager.h"

Fatso::Fatso(float posX, float posY, float posZ, Player* player, MeshInfo* mesh)
	:Mob(posX, posY, posZ, 0.f, 0.f, FATSO_JUMP, FATSO_DETECT_RADIUS, FATSO_LIFE,
	FATSO_SPEED, new PassiveAIState(this), player, FATSO_DAMAGE, mesh)
		
{
	//m_rotationFactorX = -45;
}

void Fatso::Update(float elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void Fatso::GetAttacked(MovableEntity* attacker, const int& damage)
{
	SoundManager::GetInstance()->FATSO_HURT;
}