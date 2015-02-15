#ifndef VECTOR_TWO_H__
#define VECTOR_TWO_H__

#include <cmath>
#include <ostream>
#include "define.h"

template <class T>
class Vector2 : public sf::Vector2<T>
{
public:
    Vector2(const T& x = 0, const T& y = 0);
	Vector2<T> operator-(const Vector2<T>& v) const;
	Vector2<T> operator+(const Vector2<T>& v) const;
	Vector2<T> operator*(const float multi) const;

	float Length();
	Vector2<T> Normalize();
	void Zero();

	Vector2<T> OfLength(float length);
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

template <class T>
Vector2<T>::Vector2(const T& x, const T& y) : sf::Vector2<T>(x, y)
{
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector2<T>& v)
{
	// Permet l'affichage de la position
	out << "[ " << v.x << ", " << v.y << " ]"; 
	return out;
}

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const
{
	return Vector2<T>(this->x - v.x, this->y - v.y);
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const
{
	return Vector2<T>(this->x + v.x, this->y + v.y);
}

template <class T>
float Vector2<T>::Length()
{
	//Calcul la longeur d'un vertex 
	float len = this->x*this->x + this->y*this->y;
	return sqrt(len);
}

template <class T>
Vector2<T> Vector2<T>::Normalize()
{
	float len = Length();

	if(len > 0)
	{
		this->x /= len;
		this->y /= len;
	}

	return Vector2<T>(this->x, this->y);
}

template <class T>
Vector2<T> Vector2<T>::operator*(const float multi) const
{
	return Vector2<T>(this->x * multi, this->y * multi);
}

template <class T>
void Vector2<T>::Zero()
{
	this->x = 0;
	this->y = 0;
}

template <class T>
Vector2<T> Vector2<T>::OfLength(float length) {
	return Normalize() * length;
}
#endif
