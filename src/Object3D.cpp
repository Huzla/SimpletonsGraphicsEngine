#include "Object3D.hpp"

void testGlErrorsWithMsg(const char* msg)
{
    if (glGetError())
        std::cout << msg << std::endl;
};

void Object3D::init(std::vector<Triangle> triangles)
{   
    std::cout << "Creating 3D object" << std::endl;

    // Init Vertex Array Object
    glGenVertexArrays(1, &ID);

    testGlErrorsWithMsg("Invalid value for vertex array generation.");

    // Bind the Vertex Array Object.
    bind();

    glGenBuffers(1, &VBO);
    testGlErrorsWithMsg("Invalid value for vertex buffer generation.");
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    testGlErrorsWithMsg("Error binding vertex buffer.");

    // 5 attributes for each of the 3 vertices
    std::vector<float> vboData;
    vboData.reserve((24*triangles.size()));

    std::cout << "Creating VBO data " << 24*triangles.size() << std::endl;
    
    
    for (auto it = triangles.begin(); it != triangles.end(); it++)
    {
        vboData.push_back(it->vertices.a->pos.x);
        vboData.push_back(it->vertices.a->pos.y);
        vboData.push_back(it->vertices.a->pos.z);
        vboData.push_back(it->vertices.a->n.x);
        vboData.push_back(it->vertices.a->n.y);
        vboData.push_back(it->vertices.a->n.z);
        vboData.push_back(it->vertices.a->uv.x);
        vboData.push_back(it->vertices.a->uv.y);

        vboData.push_back(it->vertices.b->pos.x);
        vboData.push_back(it->vertices.b->pos.y);
        vboData.push_back(it->vertices.b->pos.z);
        vboData.push_back(it->vertices.b->n.x);
        vboData.push_back(it->vertices.b->n.y);
        vboData.push_back(it->vertices.b->n.z);
        vboData.push_back(it->vertices.b->uv.x);
        vboData.push_back(it->vertices.b->uv.y);

        vboData.push_back(it->vertices.c->pos.x);
        vboData.push_back(it->vertices.c->pos.y);
        vboData.push_back(it->vertices.c->pos.z);
        vboData.push_back(it->vertices.c->n.x);
        vboData.push_back(it->vertices.c->n.y);
        vboData.push_back(it->vertices.c->n.z);
        vboData.push_back(it->vertices.c->uv.x);
        vboData.push_back(it->vertices.c->uv.y);
    }

    std::cout << "VBO data created " << vboData.size()  << std::endl;

    glBufferData(GL_ARRAY_BUFFER, (sizeof(float)) * vboData.size(), vboData.data(), GL_STATIC_DRAW);
    testGlErrorsWithMsg("Error initializing vertex data.");


    // Tell OpenGl how to interpret our VBO data.

    // Position data
    glVertexAttribPointer(
        0, 
        3,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(0* sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(0);
    testGlErrorsWithMsg("Error enabling attribute array.");

    // Normal data
    glVertexAttribPointer(
        1, 
        3,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(3* sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(1);
    testGlErrorsWithMsg("Error enabling attribute array.");

    // UV coordinate data
    glVertexAttribPointer(
        2, 
        2,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(6 * sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(2);
    testGlErrorsWithMsg("Error enabling attribute array.");

    unbind();

    // Unbind array buffer after vertex array.
    // If it is unbound before the unbind call will be registered to the VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    testGlErrorsWithMsg("Error unbinding buffer array.");
};

void Object3D::init(const Object3D &target)
{
    std::cout << "Creating 3D object by copying" << std::endl;

    std::cout << "Copying target VBO id" << std::endl;
    // Copy VBO id from target.
    VBO = target.VBO;

    std::cout << "ID copied successfully" << std::endl;

   // Init Vertex Array Object
    glGenVertexArrays(1, &ID);

    testGlErrorsWithMsg("Invalid value for vertex array generation.");

    // Bind the Vertex Array Object.
    bind();

    // Reuse VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    testGlErrorsWithMsg("Error binding vertex buffer.");
    // Tell OpenGl how to interpret our VBO data.

   // Position data
    glVertexAttribPointer(
        0, 
        3,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(0* sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(0);
    testGlErrorsWithMsg("Error enabling attribute array.");

    // Normal data
    glVertexAttribPointer(
        1, 
        3,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(3* sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(1);
    testGlErrorsWithMsg("Error enabling attribute array.");

    // UV coordinate data
    glVertexAttribPointer(
        2, 
        2,
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(float), 
        (void*)(6 * sizeof(float))
    );
    testGlErrorsWithMsg("Error initializing vertext attribute data.");

    glEnableVertexAttribArray(2);
    testGlErrorsWithMsg("Error enabling attribute array.");

    unbind();

    // Unbind array buffer after vertex array.
    // If it is unbound before the unbind call will be registered to the VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    testGlErrorsWithMsg("Error unbinding buffer array.");
};

void Object3D::bind() const
{
    glBindVertexArray(ID);
    
    testGlErrorsWithMsg("Error binding vertex array.");
};

void Object3D::unbind() const
{
    // Unbind vertex array
    glBindVertexArray(0);
    testGlErrorsWithMsg("Error unbinding vertex array.");
};