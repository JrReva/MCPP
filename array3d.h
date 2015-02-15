#ifndef ARRAY3D_H__
#define ARRAY3D_H__

#include "define.h"
#include <iostream>
#include <string>
#include <fstream>

template <class T>
class Array3d
{
public:
    Array3d(int x, int y, int z);
    ~Array3d();
    Array3d(const Array3d<T>& array);

    void Set(int x, int y, int z, T type);
    T Get(int x, int y, int z) const;

	void SaveTo(std::ofstream& fichier);
	void LoadTo(std::ifstream& fichier);

    void Reset(T type);
	void SaveTo(std::ostream& f);

	void FreeMemory();
private:
    int m_x, m_y, m_z;
    T* m_blocs;
		
    T& GetElement(int x, int y, int z);
    const T& GetElement(int x, int y, int z) const;
};

template <class T>
void Array3d<T>::FreeMemory() {
	for(int i = 0; i < m_x * m_y * m_z; ++i) {
		delete m_blocs[i];
	}
}

template <class T>
Array3d<T>::Array3d(int x, int y, int z) : m_x(x), m_y(y), m_z(z)
{
    m_blocs = new T[m_x * m_y * m_z];
}

template <class T>
Array3d<T>::~Array3d()
{
    delete [] m_blocs;
}

template <class T>
Array3d<T>::Array3d(const Array3d<T>& array)
{
    m_x = array.m_x;
    m_y = array.m_y;
    m_z = array.m_z;

    m_blocs = new T[m_x * m_y * m_z];
    for(int i = 0; i < m_x * m_y * m_z; ++i)
        m_blocs[i] = array.m_blocs[i];
}

template <class T>
void Array3d<T>::Set(int x, int y, int z, T type)
{
    GetElement(x, y, z) = type;
}

template <class T>
T Array3d<T>::Get(int x, int y, int z) const
{
    return GetElement(x, y, z);
}

template <class T>
void Array3d<T>::Reset(T type)
{
    for(int i = 0; i < m_x * m_y * m_z; ++i)
        m_blocs[i] = type;
}

template <class T>
T& Array3d<T>::GetElement(int x, int y, int z)
{
    return m_blocs[x + (z * m_x) + (y * m_z * m_x)];
}

template <class T>
const T& Array3d<T>::GetElement(int x, int y, int z) const
{
    return m_blocs[x + (z * m_x) + (y * m_z * m_x)];
}

template <class T>
void Array3d<T>::SaveTo(std::ofstream& fichier)	
{
	fichier.write((const char*)m_blocs, m_x*m_y*m_z);
}

template <class T>
void Array3d<T>::LoadTo(std::ifstream& fichier)
{
	fichier.read((char*)m_blocs, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
	fichier.close();
}

#endif // ARRAY3D_H__
