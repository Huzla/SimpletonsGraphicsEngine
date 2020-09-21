#include "TriVertices.hpp"

class Triangle
{
public:
    TriVertices vertices;
    glm::vec3   u;
    glm::vec3   v;
    glm::vec3   n;
    float       area;

    Triangle(Vertex* a, Vertex* b, Vertex* c);
};