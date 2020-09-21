#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Object3D.hpp"

const float windowWidth = 800.0f;
const float windowHeight = 600.0f;
const float mouseSensitivity = 0.05f;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// delta time for smooth movement of camera.
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera sceneCamera;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{   
    // Close window on escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Define camera actions.
    if (action == GLFW_PRESS || action == GLFW_RELEASE)
    {
        GLboolean moveOrStop = action == GLFW_PRESS;

        switch (key) {
            case GLFW_KEY_W:
                sceneCamera.processKeyboard(FORWARD, moveOrStop);
                break;
            case GLFW_KEY_S:
                sceneCamera.processKeyboard(BACKWARD, moveOrStop);
                break;
            case GLFW_KEY_A:
                sceneCamera.processKeyboard(LEFT, moveOrStop);
                break;
            case GLFW_KEY_D:
                sceneCamera.processKeyboard(RIGHT, moveOrStop);
                break;
            default:
                break;
        }
        }
    }

float mouseLastX = windowWidth * 0.5f;
float mouseLastY = windowHeight * 0.5f;
bool mousePosFirstFlag = true;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (mousePosFirstFlag)
    {
        mouseLastX = xPos;
        mouseLastY = yPos;
        mousePosFirstFlag = false;
    }

    // Calculate change from last mouse position and add it to yaw and pitch.
    float mouseOffsetX = xPos - mouseLastX;
    float mouseOffsetY = mouseLastY - yPos; // y coordinates increase from bottom to top.

    mouseLastX = xPos;
    mouseLastY = yPos;

    sceneCamera.processMouseMovement(mouseOffsetX, mouseOffsetY);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    sceneCamera.processMouseScroll(yOffset);
}

int main()
{   
    // Init camera directon.
    sceneCamera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), FOV, YAW, PITCH, WALK);
    
    // configure GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_REFRESH_RATE, 60);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ExPose all extensions with valid entry points.
    // http://glew.sourceforge.net/basic.html Experimental Drivers
    glewExperimental=GL_TRUE;

    // Initilize extension entry points.
    GLenum err=glewInit();
    if(err!=GLEW_OK)
    {
        //Problem: glewInit failed, something is seriously wrong.
        std::cout<<"glewInit failed, aborting."<<std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // Define vertex data
    std::vector<Vertex> vertices = {
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),

        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),

        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),

        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        
        Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),

        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f, -0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        
        Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),

        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        
        Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f)
    };

    std::vector<Triangle> cubeTriangles;
    cubeTriangles.reserve(vertices.size() / 3);
    unsigned int vertIndex = 0;

    std::cout << "Creating triangles" << std::endl;

    for (int index = 0; index < (vertices.size() / 3); index++)
    {
        std::cout << vertices[vertIndex].pos.x << std::endl;
        cubeTriangles.push_back(Triangle(&vertices[vertIndex], &vertices[vertIndex + 1], &vertices[vertIndex + 2]));

        vertIndex += 3;
    }

    std::cout << "Triangles created succesfully " << cubeTriangles.size() << std::endl;

    Object3D simpleCube, lightCube;

    simpleCube.init(cubeTriangles);
    lightCube.init(simpleCube);

    Shader simpleShader("./shaders/simpleCubeVS.glsl", "./shaders/simpleCubeFS.glsl");
    Shader lightShader("./shaders/lightCubeVS.glsl", "./shaders/lightCubeFS.glsl");
    Texture containerTexture(GL_TEXTURE_2D, GL_RGB, 0, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, "./container.jpg");
    Texture smileyTexture(GL_TEXTURE_2D, GL_RGBA, 1, GL_REPEAT, GL_REPEAT, "./awesomeface.png");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        // Set clear color
        glClearColor(0.3f, 0.3f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Get current render time and update delta time.
        float currentRenderTime = glfwGetTime();
        deltaTime = currentRenderTime - lastFrame;
        lastFrame = currentRenderTime;

        sceneCamera.move(deltaTime);

        glfwSetKeyCallback(window, key_callback);
        
        simpleShader.activate();
        containerTexture.bind();
        smileyTexture.bind();

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.2f,  1.0f, -1.5f)  
        };

        simpleShader.setInt("texture1", 0);
        simpleShader.setInt("texture2", 1);

        simpleCube.bind();

        glm::mat4 view;
        view = sceneCamera.getViewMatrix();

        glm::mat4 projection;
        projection = glm::perspective(sceneCamera.getFovRads(), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::vec3 viewSpaceLightPos = glm::vec3(view * glm::vec4(lightPos, 1.0f));

        simpleShader.setVec3f("lightColor", lightColor);
        simpleShader.setVec3f("lightPos", viewSpaceLightPos); // Lighting calculations done in view space.
        simpleShader.setMat4f("projection", projection);
        
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]); 
            model = glm::rotate(model, currentRenderTime * glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 cubeTransformation = view * model;

            simpleShader.setMat4f("viewModel", cubeTransformation);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        simpleCube.unbind();
        simpleShader.deactivate();
        containerTexture.unbind();
        smileyTexture.unbind();

        // Draw light cube
        lightShader.activate();
        lightCube.bind();
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 

        glm::mat4 lightTransform = projection * view * model;
        lightShader.setMat4f("transformation", lightTransform);
        simpleShader.setVec3f("lightColor", lightColor);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightCube.unbind();
        lightShader.deactivate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}