#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "define.h"
#include "tool.h"
#include <iostream>
#include <cassert>

class Shader
{
    public:    
        bool Load(const std::string& vertFile, const std::string& fragFile, bool verbose = false);
        void Use() const;


        void UpdateIntUniform(const std::string& name, GLint value) const;
        void UpdateFloatUniform(const std::string& name, GLfloat value) const;
		void UpdateVec4Uniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

        static void Disable();

    public: // TODO remettre ca private...
        GLenum m_program;
        GLenum m_vertexShader;
        GLenum m_fragmentShader;

    private:
        bool CheckShaderError(GLenum shader, bool verbose);
        bool CheckProgramError(GLenum program, bool showWarning, bool verbose);
};


#endif // SHADER_H
