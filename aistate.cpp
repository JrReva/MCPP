#include "aistate.h"
#include "mob.h"
#include <math.h>

AIState::AIState(Mob* mob, MovableEntity* target)
	: m_mob(mob), m_target(target)
{
}

float AIState::FindAngleWithTarget() const
{
	//S'il n'y a pas de target.
	if(m_target == NULL)
		return 0.f;

	//On obtient un triangle de la distance entre les deux entités.
	Vector3f distance = m_target->Position() - m_mob->Position();
	float a = 0, b = 0, offset = 0;

	//Si on travaille dans le quadrant 2 ou 4 (une seule valeur négative)...
	if((distance.x < 0 && distance.z >= 0) || (distance.x >= 0 && distance.z < 0))
	{
		a = distance.x;
		b = distance.z;

		//Quandrant 2.
		if(distance.z < 0)
			offset = 180.f;

		//Quandrant 4; offset = 0.
	}
	else	//...Quandrants 1 et 3
	{
		a = distance.z;
		b = distance.x;

		//On travaille dans le quadrant 1.
		if(distance.x >= 0)
			offset = 90.f;
		else	//...Quandrant 3.
			offset = 270.f;
	}

	//On retourne l'angle résultat, moins son offset.
	return offset - (atan(a / b) * 180.f / 3.1416f);
}