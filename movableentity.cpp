#include "movableentity.h"
#include "soundmanager.h"
#include "player.h"

MovableEntity::MovableEntity(float posX, float posY, float posZ, float rotX, float rotY, float jump, int life, 
	float hauteur, float largeur, float normalSpeed, float flyingSpeed, float runningSpeed, int damage)
	: m_vector(posX, posY, posZ), m_rotVector(rotX, rotY), m_jumpForce(jump), m_life(life),
	m_hauteur(hauteur), m_largeur(largeur), m_onGround(false), m_fly(false), m_run(false), m_moveVector(0, 0),
	m_runningSpeed(runningSpeed), m_flyingSpeed(flyingSpeed), m_normalSpeed(normalSpeed), m_moveAttempt(m_vector),
	m_velocity(0), m_jump(false), m_damage(damage), m_knockbackET(KNOCKBACK_DURATION), m_rotationFactorX(0)
{
	RefreshSpeed();
	m_mesh = NULL;
}

MovableEntity::~MovableEntity() { }

void MovableEntity::MoveSimulation(const float& elapsedTime)
{
	float tempX = 0.f, tempY = 0.f, tempZ = 0.f;


	if(m_knockbackET < 2.f)
		m_knockbackET += elapsedTime;

	Jump(elapsedTime);
	ApplyGravity(elapsedTime, tempY);

	//On applique les mouvements de l'entit?
	ApplyMove(elapsedTime, tempX, tempZ);

	m_moveAttempt = Vector3f(tempX, tempY, tempZ);
}

void MovableEntity::Jump(const float& elapsedTime)
{
	//Conditions d'application du saut.
	if((m_onGround || m_fly) && m_jump)
	{
		if(m_fly == false && dynamic_cast<Player*>(this) != 0)
		{
			SoundManager::GetInstance()->StartSound(SoundManager::JUMP);
		}
		//On applique le saut.
		m_velocity = m_jumpForce;
		m_onGround = false;
	}
}

void MovableEntity::Render() const
{
	if(m_mesh != NULL)
	{
		glPushMatrix();

		ApplyRotation();
		ApplyTranslation();

		m_mesh->Render();

		glPopMatrix();
	}
}

void MovableEntity::ApplyRotation() const
{
	glRotatef(GetRotY(),1,0,0);
	glRotatef(-GetRotX() + m_rotationFactorX + 180,0,1,0);
}

void MovableEntity::ApplyTranslation() const
{
	glTranslatef((m_vector.x + abs(m_offset.x)) - .5f, m_vector.y + m_offset.y  - .5f, (m_vector.z + abs(m_offset.z)) - .5f);
}

void MovableEntity::ApplyGravity(const float& elapsedTime, float& tempY)
{
	tempY = m_vector.y;
	
	if(!m_onGround) {
		tempY += (m_velocity * elapsedTime) + (0.5 * GRAVITY * elapsedTime * elapsedTime);
		m_velocity += GRAVITY * elapsedTime;
	}

	if(m_fly && tempY < m_vector.y) {
		tempY = m_vector.y;
		m_velocity = 0;
	}
}

void MovableEntity::ApplyMove(const float& elapsedTime, float& tempX, float& tempZ)
{
	Vector2f normalized;
	
	if(m_knockbackET < 2.f)
	{
		normalized = m_knockback.Normalize();
	}
	else
	{
	    normalized = m_moveVector.Normalize();
	}

	tempX = m_vector.x;
	tempZ = m_vector.z;
	float rad = m_rotVector.x / 180 * 3.141592654f;
	
	tempZ += ((normalized.x * cos(rad)) - (normalized.y * sin(rad))) * m_actualSpeed * elapsedTime;
	tempX += ((normalized.y * cos(rad)) + (normalized.x * sin(rad))) * m_actualSpeed * elapsedTime;
}

void MovableEntity::Attack(MovableEntity* target)
{
	//On attaque la target d?sign?e en lui faisant du dommage selon ce qui est sp?cifi?.
	target->GetAttacked(this, m_damage);
}

void MovableEntity::GetAttacked(MovableEntity* attacker, const int& damage)
{
	m_life -= damage;

	float pushback_x = 0.F;
	float pushback_z = 0.F;

	if(Position().x < attacker->Position().x)
	{
		pushback_x = -1.F;
	}
	else if(Position().x > attacker->Position().x)
	{
		pushback_x = 1.f;
	}
	if(Position().z < attacker->Position().z)
	{
		pushback_z = -1.F;
	}
	else if(Position().z > attacker->Position().z)
	{
		pushback_z = 1.F;
	}

	m_knockback.x = pushback_x/KNOCKBACK_DURATION;
	m_knockback.y = pushback_z/KNOCKBACK_DURATION;
	m_knockbackET = 0.f;
}

Vector3f MovableEntity::Position() const
{
	return m_vector + m_offset;
}

float MovableEntity::GetRotX() const
{
	return m_rotVector.x;
}

void MovableEntity::SetRotX(float x) {
	m_rotVector.x = x;
}

void MovableEntity::SetRotY(float y) {
	m_rotVector.y = y > 90 ? 90 : y < -90 ? -90 : y;
}

float MovableEntity::GetRotY() const
{
	return m_rotVector.y;
}

Vector3f MovableEntity::MoveAttempt() const {
	return m_moveAttempt;
}

void MovableEntity::MoveAttempt(const Vector3f moveAttempt) {
	m_moveAttempt = moveAttempt;
}

// Positionne le joueur sur le jeu, apr?s les test de collisions
void MovableEntity::SetPosition(const Vector3f v)
{
	m_vector = v;
}

float MovableEntity::Largeur() const { return m_largeur; }
float MovableEntity::Hauteur() const { return m_hauteur; }

void MovableEntity::ResetVelocity()
{
	m_velocity = 0;
}

//Calcule la distance entre l'entit? actuelle et celle pass?e en param?tre.
float MovableEntity::CalculateDistance(MovableEntity* otherEntity) const
{
	return (Position() - otherEntity->Position()).Length();
}

float MovableEntity::Calculate2DDistance(MovableEntity* otherEntity) const
{
	Vector3f v = Position() - otherEntity->Position();
	v.y = 0;

	return v.Length();
}

Cube MovableEntity::GetCube() const {
	Vector3f pos = Position();	//On obtient la position avec l'offset
	return Cube(pos.x, pos.y, pos.z, m_largeur, m_hauteur);
}

bool MovableEntity::IsOnGround() const {
	return m_onGround;
}

void MovableEntity::SetOnGround(bool onGround) {
	if(onGround)
		m_velocity = 0;

	m_onGround = onGround;
}

bool MovableEntity::IsFlying() const {
	return m_fly;
}

void MovableEntity::SetFly(bool fly) {
	m_fly = fly;
	RefreshSpeed();
}

void MovableEntity::SetMoveVector(float x, float y) {
	m_moveVector.x = x;
	m_moveVector.y = y;
}

void MovableEntity::SetMoveX(float x) {
	SetMoveVector(x, m_moveVector.y);
}

void MovableEntity::SetMoveY(float y) {
	SetMoveVector(m_moveVector.x, y);
}

bool MovableEntity::IsRunning() const {
	return m_run;
}

void MovableEntity::SetRun(bool run) {
	m_run = run;

	RefreshSpeed();
}

bool MovableEntity::IsJumping() const {
	return m_jump;
}

void MovableEntity::SetJump(bool jump) {
	m_jump = jump;
}

bool MovableEntity::IsDead() const { return m_life <= 0; }

void MovableEntity::RefreshSpeed() {
	if(m_fly)
		m_actualSpeed = m_flyingSpeed;
	else if(m_run)
		m_actualSpeed = m_runningSpeed;
	else
		m_actualSpeed = m_normalSpeed;
}
