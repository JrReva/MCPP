#include "texture.h"

Texture::Texture(const char* filename) : m_isValid(false), m_filename(filename)
{
    //if(filename != "")
    //    Load(filename);
}

Texture::~Texture()
{
    if(IsValid())
        glDeleteTextures(1, &m_textureId);
}

bool Texture::Load() {
	return Load(m_filename);
}

bool Texture::Load(const char* filename)
{
    // Initialize Devil only once:
    static bool alreadyInitialized = false;
    if(!alreadyInitialized)
    {
        ilInit();
        alreadyInitialized = true;
    }

    // Use Devil library to load image data in memory
    ILuint texid;
    ilGenImages(1, &texid);
    ilBindImage(texid);

	//Reverse origin
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilEnable(IL_ORIGIN_SET);

    if (!ilLoadImage((const ILstring)filename))
        return false;

    if (!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
        return false;

    // Create mipmapped opengl texture from image data

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),  ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

	ilDeleteImages(1, &texid);
    m_isValid = true;
    return true;
}

bool Texture::IsValid() const
{
    return m_isValid;
}

void Texture::Bind() const
{
    assert(IsValid());
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

