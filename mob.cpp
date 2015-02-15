#include "mob.h"
#include "define.h"
#include "preferences.h"

//Constructeur de Mob
Mob::Mob(float posX, float posY, float posZ, float rotX, float rotY, float jump, float detectRadius, int life,
		float speed, AIState* initState, Player* player, int damage, MeshInfo* mesh)
		:MovableEntity(posX, posY, posZ, rotX, rotY, jump, life, 0, 0, speed, speed, 0, damage),
		m_currentState(initState), m_player(player), m_lastPosition(posX, posY, posZ), m_detectRadius(detectRadius),
		m_dispose(false), m_render(false)
{
	m_mesh = mesh;
	m_hauteur = mesh->GetHeight();
	m_largeur = mesh->GetWidth();
	m_offset = mesh->GetOffset();
}

Mob::~Mob()
{
	delete m_currentState;
}

//On r?affecte l'?tat du Mob.
void Mob::SetAIState(AIState* newState)
{
	//On lib?re la m?moire pour ?viter un Memory Leak.
	delete m_currentState;
	//On assigne la nouvelle IA.
	m_currentState = newState;
}

void Mob::MoveSimulation(const float& elapsedTime)
{
	float distance = Calculate2DDistance(m_player);

	//On marque le mob pour la destruction s'il est trop loin (en distance 2D).
	m_dispose = distance >= Preferences::GetMobDisposeDistance();
	m_render = distance <= Preferences::GetMobRenderDistance();

	//On appelle la méthode de la classe mère seulement si le mob n'a pas besoin
	//d'être détruit.
	if(!m_dispose)
		MovableEntity::MoveSimulation(elapsedTime);
}

void Mob::Render() const
{
	if(m_mesh != NULL)
	{
		glPushMatrix();

		ApplyTranslation();
		ApplyRotation();
		

		m_mesh->Render();

		glPopMatrix();
	}
}