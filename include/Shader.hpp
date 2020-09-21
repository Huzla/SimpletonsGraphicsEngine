#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/glu.h>
#include <fstream>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // shader program ID
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    // use this shader program for rendering.
    void activate();
    void deactivate();

    void setBool(const char* name, bool value) const;
    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;
    void setMat4f(const char* name, glm::mat4 &trans) const;
    void setVec4f(const char* name, glm::vec4 &vec) const;
    void setVec3f(const char* name, glm::vec3 &vec) const;
};

#endif