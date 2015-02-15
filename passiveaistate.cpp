#include "passiveaistate.h"
#include "mob.h"
#include "random.h"

PassiveAIState::PassiveAIState(Mob* mob)
	: AIState(mob), m_actionTime(0), m_rotX(mob->GetRotX()), m_moving(false), m_rand(Random::GetInstance())
{
}

void PassiveAIState::Update(const float& elapsedTime)
{
	//L'IA passif ne fait que se promener, sans se soucier du player...
	if((m_actionTime-=elapsedTime) <= 0)
	{
		m_actionTime = m_rand->GetNextFloat(1,9);	//Next action will take place from 1s to 8s.
		m_moving = m_rand->GetNext(100) % 3;		//1 chance out of 3 to not move on the next panel.
		
		if(m_moving)
		{
			m_rotX = m_rand->GetNext(8);			//Rotate the mob between 0 and 360 degrees.

			m_mob->SetRotX(45*m_rotX);
			m_mob->SetMoveY(1);
		}
		else
		{
			m_mob->SetMoveX(0);
		}
		
		m_mob->SetJump(m_rand->GetNext(100) % 4 == 0);
	}
}