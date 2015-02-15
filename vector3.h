#ifndef VECTOR_H__
#define VECTOR_H__

#include <cmath>
#include <ostream>
#include "define.h"

template <class T>
class Vector3 : public sf::Vector3<T>
{
public:
    Vector3(const T& x = 0, const T& y = 0, const T& z = 0);
	Vector3<T> operator-(const Vector3<T>& v) const;
	Vector3<T> operator+(const Vector3<T>& v) const;
	Vector3<T> operator*(const float multi) const;

	float Length();
	Vector3<T> Normalize();

	void Zero();

};

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;

template <class T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z) : sf::Vector3<T>(x, y, z)
{
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector3<T>& v)
{
	// Permet l'affichage de la position
	out << "[ " << v.x << ", " << v.y << ", " << v.z << " ]"; 
	return out;
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
{
	return Vector3<T>(this->x - v.x, this->y - v.y, this->z - v.z);
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const
{
	return Vector3<T>(this->x + v.x, this->y + v.y, this->z + v.z);
}

template <class T>
float Vector3<T>::Length()
{
	//Calcul la longeur d'un vertex 
	float len = this->x*this->x + this->y*this->y + this->z*this->z;
	return sqrt(len);
}

template <class T>
Vector3<T> Vector3<T>::Normalize()
{
	float len = Length();

	if(len > 0)
	{
		this->x /= len;
		this->y /= len;
		this->z /= len;
	}

	return Vector3<T>(this->x, this->y, this->z);
}

template <class T>
Vector3<T> Vector3<T>::operator*(const float multi) const
{
	return Vector3<T>(this->x * multi, this->y * multi, this->z * multi);
}

template <class T>
void Vector3<T>::Zero()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
#endif
