#include <glm/glm.hpp>

struct Vertex
{
    Vertex(glm::vec3 pos) : pos(pos), n(1.0f), uv(-1.0f) {};
    Vertex(glm::vec3 pos, glm::vec2 uv) : pos(pos), uv(uv), n(1.0f) {};
    Vertex(float x, float y, float z, float u, float v) : pos(x, y, z), uv(u, v), n(1.0f) {};
    glm::vec3   pos;
    glm::vec3   n;
    glm::vec2   uv;   
};

struct TriVertices
{
    
    Vertex* a;
    Vertex* b;
    Vertex* c;
};