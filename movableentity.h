#ifndef MOVABLE_ENTITY__
#define MOVABLE_ENTITY__

#include <string>
#include <math.h>

#include "define.h"
#include "vector3.h"
#include "vector2.h"
#include "cube.h"
#include "chunkmesh.h"
#include "texture.h"
#include "meshinfo.h"

class MovableEntity
{
//Constructeur(s) et destructeur...
public :
	MovableEntity(float posX, float posY, float posZ, float rotX, float rotY, float jump, int life, 
	float hauteur, float largeur, float normalSpeed, float flyingSpeed, float runningSpeed, int damage);
	virtual ~MovableEntity() = 0;

//Méthodes publiques...
public :
	float CalculateDistance(MovableEntity* otherEntity) const;
	float Calculate2DDistance(MovableEntity* otherEntity) const;
	virtual void MoveSimulation(const float& elapsedTime);

	virtual void Render() const;

	virtual void ApplyRotation() const;
	virtual void ApplyTranslation() const;

	void virtual Attack(MovableEntity* target);
	void virtual GetAttacked(MovableEntity* attacker, const int& damage);
//Accesseurs...
public :
	void SetPosition(const Vector3f vv);
	Vector3f Position() const;

	Vector3f MoveAttempt() const;
	void MoveAttempt(const Vector3f moveAttempt);

	Vector3f GetOffset() const { return m_offset; }

	float Largeur() const;
	float Hauteur() const;
	
	float GetRotX() const;
	void SetRotX(float x);

	float GetRotY() const;
	void SetRotY(float x);
	
	void ResetVelocity();
	void GraviteActif(bool value);

	Cube GetCube() const;
	bool IsOnGround() const;
	void SetOnGround(bool onGround);
	
	bool IsFlying() const;
	void SetFly(bool fly);

	bool IsRunning() const;
	void SetRun(bool run);

	bool IsJumping() const;
	void SetJump(bool jump);

	bool IsDead() const;
	
	void SetMoveVector(float x, float y);
	void SetMoveX(float x);
	void SetMoveY(float y);

//Méthodes protected...
protected :
	void Jump(const float& elapsedTime);	
	void ApplyGravity(const float& elapsedTime, float& tempY);
	void ApplyMove(const float& elapsedTime, float& tempX, float& tempZ);
	void RefreshSpeed();

//Champs protected...
protected :
	float m_hauteur, m_largeur;
	float m_velocity, m_jumpForce, m_knockbackET;
	float m_runningSpeed, m_normalSpeed, m_flyingSpeed, m_actualSpeed;
	bool m_graviteActif;
	Vector3f m_vector, m_moveAttempt, m_offset;
	Vector2f m_moveVector, m_rotVector, m_knockback;
	int m_life, m_damage;
	bool m_onGround, m_fly, m_run, m_jump;
	float m_rotationFactorX;

	MeshInfo* m_mesh;
};

#endif