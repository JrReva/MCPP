#ifndef CUBE_H__
#define CUBE_H__

#include "vector3.h"

enum CollisionSide {
	COLLISION_X = 1, 
	COLLISION_Y = 2, 
	COLLISION_Z = 4
};

enum CollisionPosition {
	COLLISION_TOP,
	COLLISION_BOTTOM,
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_FRONT,
	COLLISION_BACK,
	COLLISION_NONE
};

class Cube {
public:
	Cube(float x, float y, float z, float w, float h);
	bool InCollisionWith(const Cube& cube) const;
	int GetCollisionWith(const Cube& cube) const;
	CollisionPosition GetMaxPosition(const Cube start, Cube& destination) const;

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float x, y, z, w, h;
};


#endif
