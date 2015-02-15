#ifndef PLAYER_H__
#define PLAYER_H__

#include <iostream>
#include "openglcontext.h"
#include "vector3.h"
#include "chunk.h"
#include "movableentity.h"

class Player : public MovableEntity
{
public:
	Player(float posX = WORLD_CENTER, float posY = PLAYER_START_HEIGHT, float posZ = WORLD_CENTER, float rotX = 0, float rotY = 0);
	~Player();

	void TurnLeftRight(float value);
	void TurnTopBottom(float value);

	virtual void ApplyTranslation() const;
	virtual void Render() const;

	Vector3f GetCameraPosition() const;

public :
	void virtual Attack(MovableEntity* target);
	void virtual GetAttacked(MovableEntity* attacker, int damage);
};

#endif
