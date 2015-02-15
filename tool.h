#ifndef TOOL_H__
#define TOOL_H__

#include <string>
#include "define.h"
#include <cassert>
#include <iostream>
#include <fstream>

// TODO ne pas oublier de ne pas definir DEBUGMODE en release
#ifndef DEBUGMODE
#define DEBUGMODE
#endif

#ifdef DEBUGMODE
#	define CHECK_GL_ERROR() Tool::CheckGLError(__FILE__, __LINE__);
#else
#	define CHECK_GL_ERROR()
#endif


class Tool
{
public:
    static void CheckTypes();
    static bool LoadTextFile(const std::string& filename, std::string& buffer);
    static void CheckGLError(const char* file, int line);

	template <class T>
	static bool EqualWithEpsilon(const T& v1, const T& v2, T epsilon = T(EPSILON))
	{
		return (fabs(v2 - v1) < epsilon);
	}

	template <class T>
	static bool InRangeWithEpsilon(const T& v, const T& vinf, const T& vsup, T epsilon = T(EPSILON))
	{
		return (v + epsilon >= vinf - epsilon && v - epsilon <= vsup + epsilon);
	}

	template <class T>
	static bool InRangeWithoutEpsilon(const T& v, const T& vinf, const T& vsup, T epsilon = T(EPSILON))
	{
		return (v - epsilon >= vinf + epsilon && v + epsilon <= vsup - epsilon);
	}
};



#endif // TOOL_H__
