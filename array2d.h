#ifndef ARRAY2D_H__
#define ARRAY2D_H__

#include "define.h"

template <class T>
class Array2d
{
public:
    Array2d(int x, int y);
    ~Array2d();
    Array2d(const Array2d<T>& array);

    void Set(int x, int y, T type);
    T Get(int x, int y) const;
	int GetSizeX() const;
	int GetSizeY() const;

    void Reset(T type);

	void FreeMemory();
private:
    int m_x, m_y;
    T* m_blocs;
		
    T& GetElement(int x, int y);
    const T& GetElement(int x, int y) const;
};


template <class T>
void Array2d<T>::FreeMemory() {
	for(int i = 0; i < GetSizeX() * GetSizeY(); ++i) {
		delete m_blocs[i];
	}
}

template <class T>
Array2d<T>::Array2d(int x, int y) : m_x(x), m_y(y)
{
    m_blocs = new T[m_x * m_y];
}

template <class T>
Array2d<T>::~Array2d()
{
    delete [] m_blocs;
}

template <class T>
Array2d<T>::Array2d(const Array2d<T>& array)
{
    m_x = array.m_x;
    m_y = array.m_y;

    m_blocs = new T[m_x * m_y];
    for(int i = 0; i < m_x * m_y; ++i)
        m_blocs[i] = array.m_blocs[i];
}

template <class T>
void Array2d<T>::Set(int x, int y, T type)
{
    GetElement(x, y) = type;
}

template <class T>
T Array2d<T>::Get(int x, int y) const
{
    return GetElement(x, y);
}

template <class T>
T& Array2d<T>::GetElement(int x, int y)
{
    return m_blocs[x + (y * m_x)];
}

template <class T>
void Array2d<T>::Reset(T type)
{
    for(int i = 0; i < m_x * m_y; ++i)
        m_blocs[i] = type;
}

template <class T>
const T& Array2d<T>::GetElement(int x, int y) const
{
    return m_blocs[x + (y * m_x)];
}

template <class T>
int Array2d<T>::GetSizeX() const
{
	return m_x;
}

template <class T>
int Array2d<T>::GetSizeY() const
{
	return m_y;
}

#endif // ARRAY2D_H__
