#include "cube.h"
#include "tool.h"

Cube::Cube(float x, float y, float z, float w, float h) : x(x), y(y), z(z), w(w), h(h) {
	
}

int Cube::GetCollisionWith(const Cube& cube) const {
	int side = COLLISION_X | COLLISION_Y | COLLISION_Z;
	
	if(!Tool::InRangeWithoutEpsilon(cube.x, x - cube.w, x + w))
		side ^= COLLISION_X;
	if(!Tool::InRangeWithoutEpsilon(cube.y, y - cube.h, y + h))
		side ^= COLLISION_Y;
	if(!Tool::InRangeWithoutEpsilon(cube.z, z - cube.w, z + w))
		side ^= COLLISION_Z;

	return side;
}

bool Cube::InCollisionWith(const Cube& cube) const {
	if(!Tool::InRangeWithoutEpsilon(cube.x, x - cube.w, x + w))
		return false;
	if(!Tool::InRangeWithoutEpsilon(cube.y, y - cube.h, y + h))
		return false;
	if(!Tool::InRangeWithoutEpsilon(cube.z, z - cube.w, z + w))
		return false;

	return true;
}

CollisionPosition Cube::GetMaxPosition(const Cube start, Cube& destination) const {
	if(!(GetCollisionWith(Cube(start.x, destination.y, destination.z, destination.w, destination.h)) & COLLISION_X)) {
		if(start.x > destination.x) {
			destination.x = x + w;
			return COLLISION_LEFT;
		} else {
			destination.x = x - destination.w;
			return COLLISION_RIGHT;
		}
	}
	
	if(!(GetCollisionWith(Cube(destination.x, destination.y, start.z, destination.w, destination.h)) & COLLISION_Z)) {
		if(start.z > destination.z) {
			destination.z = z + w;
			return COLLISION_BACK;
		} else {
			destination.z = z - destination.w;
			return COLLISION_FRONT;
		}
	}

	if(!(GetCollisionWith(Cube(destination.x, start.y, destination.z, destination.w, destination.h)) & COLLISION_Y)) {
		if(start.y >= destination.y) {
			destination.y = y + h;
			return COLLISION_BOTTOM;
		} else {
			destination.y = y - destination.h;
			return COLLISION_TOP;
		}
	}

	return COLLISION_NONE;
}
