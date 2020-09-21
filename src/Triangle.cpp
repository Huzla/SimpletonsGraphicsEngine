#include "Triangle.hpp"

Triangle::Triangle(Vertex* a, Vertex* b, Vertex* c)  : vertices{ a, b, c }
{
    u = c->pos - a->pos;
    v = b->pos - a->pos;

    glm::vec3 temp = glm::cross(u, v);
    area = 0.5f * glm::length(temp);
    n = glm::normalize(temp);

    a->n = n;
    b->n = n;
    c->n = n;
};  