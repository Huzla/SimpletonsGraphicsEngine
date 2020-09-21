#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Triangle.hpp"

class Object3D 
{
public:
    // Used for binding this object. 
    // In practice this is the VAO ID.
    GLuint ID;

    // vertices contains vertex data
    // attributeDesc contains a description of how the vertex data is sequenced. It is used to make calls to glVertexAttribPointer. 
    void init(std::vector<Triangle> triangles);
    void init(const Object3D &target);

    void bind() const;
    void unbind() const;

protected:
    GLuint VBO;
};

#endif