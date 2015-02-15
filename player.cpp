#include "player.h"
#include "menucoeur.h"

Player::Player(float posX, float posY, float posZ, float rotX, float rotY)
	:MovableEntity(posX, posY, posZ, rotX, rotY, SAUT_PERSO, PLAYER_LIFE, HAUTEUR_JOUEUR, LARGEUR_JOUEUR, PLAYER_SPEED, PLAYER_FLYING_SPEED, PLAYER_RUNNING_SPEED, PLAYER_DAMAGE)
{
}

Player::~Player()
{
	std::cout << "Player is dead" << std::endl;
}

void Player::Render() const
{
	ApplyRotation();
	ApplyTranslation();
	
}

void Player::TurnLeftRight(float value)
{
	SetRotX(GetRotX() + (value / MM_DIVISION));
}

void Player::TurnTopBottom(float value)
{
	SetRotY(GetRotY() + (value / MM_DIVISION));
}

void Player::ApplyTranslation() const
{
	Vector3f vector = GetCameraPosition();
	glTranslatef(-vector.x, -vector.y, -vector.z);
}

void Player::Attack(MovableEntity* target)
{
	target->GetAttacked(this, 10);
}

void Player::GetAttacked(MovableEntity* attacker, int damage)
{
    m_life -= damage;

	MenuCoeur::GetInstance()->SetNbCoeur(m_life);
}

Vector3f Player::GetCameraPosition() const {
	return Vector3f(m_vector.x + m_largeur / 2, m_vector.y + HAUTEUR_CAMERA, m_vector.z + m_largeur / 2);
}