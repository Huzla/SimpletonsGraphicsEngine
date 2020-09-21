#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
private:
    GLenum targetTexture;
    GLenum textureUnit;

public:
    unsigned int ID;
    int width;
    int height;
    int nrChannels;

    Texture(GLenum target, GLenum format, unsigned int textureUnitIn, GLenum wrappingOptionS, GLenum wrappingOptionT,  const char* filepath);
    void bind() const;
    void unbind() const;
};

#endif