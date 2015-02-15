#ifndef TEXTURE_H__
#define TEXTURE_H__

#include "define.h"
#include <IL/il.h>
#include <string>
#include <cassert>

class Texture
{
public:
    Texture(const char* filename = "");
    ~Texture();

    bool Load();
    bool Load(const char* filename);
    bool IsValid() const;
    void Bind() const;

private:
    GLuint  m_textureId;
    bool    m_isValid;
    const char* m_filename;
};

#endif // TEXTURE_H__
