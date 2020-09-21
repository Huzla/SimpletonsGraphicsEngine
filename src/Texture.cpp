#include "Texture.hpp"

Texture::Texture(GLenum target, GLenum format, unsigned int textureUnitIn, GLenum wrappingOptionS, GLenum wrappingOptionT, const char* filepath)
{
    // TODO: Check validity of input values.
    glGenTextures(1, &ID);
    targetTexture = target;
    textureUnit = GL_TEXTURE0 + textureUnitIn;

    bind();

    // Set texture wrapping/filtering options
    // TODO: Allow passing of these options.
    glTexParameteri(targetTexture, GL_TEXTURE_WRAP_S, wrappingOptionS);
    glTexParameteri(targetTexture, GL_TEXTURE_WRAP_T, wrappingOptionT);
    glTexParameteri(targetTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(targetTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data from disk and generate the texture object.
    unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data)
    {
        // Generate texture and mipmaps
        glTexImage2D(targetTexture, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(targetTexture);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    unbind();
};


void Texture::bind() const
{
    glActiveTexture(textureUnit);
    glBindTexture(targetTexture, ID);
}

void Texture::unbind() const
{
    glBindTexture(targetTexture, 0);
    glActiveTexture(GL_TEXTURE0);
}