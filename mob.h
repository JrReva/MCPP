#ifndef MOB_H__
#define MOB_H__

#include "movableentity.h"
#include "player.h"
#include "aistate.h"
#include "aggressiveaistate.h"
#include "passiveaistate.h"
#include "scaredaistate.h"
#include "vector3.h"

class Mob : public MovableEntity
{
//Constructeur(s) et destructeur...
public :
	Mob(float posX, float posY, float posZ, float rotX, float rotY, float jump, float detectRadius, int life,
		float speed, AIState* initState, Player* player, int damage, MeshInfo* mesh);
	virtual ~Mob();

//Méthodes publiques virtuelles pures.
public :
	//Logique de mise-à-jour de la stratégie d'IA et appel d'IA.
	void virtual Update(float elapsedTime) = 0;

public :
	virtual void MoveSimulation(const float& elapsedTime);
	virtual void Render() const;

//Accesseurs...
public :
	float GetDetectRadius() const { return m_detectRadius; }
	void SetDetectRadius(float detectRadius) { m_detectRadius = detectRadius; }

	//Retourne la distance avec le joueur en 3D.
	float GetDistanceWithPlayer() const { return m_distanceWithPlayer; }

	bool GetDispose() const { return m_dispose; }
	bool GetIsRendering() const { return m_render; }

//Champs protected...
protected :
	Vector3f m_lastPosition;
	AIState* m_currentState;
	Player* m_player;

	float m_detectRadius;
	float m_distanceWithPlayer;

	bool m_dispose;
	bool m_render;

//Méthodes protected...
protected :
	void SetAIState(AIState* newState);
	
};

#endif //MOB_H__