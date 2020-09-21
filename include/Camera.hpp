#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum Camera_Mode {
    FLY,
    WALK
};

struct Camera_State {
    GLboolean forward;
    GLboolean backward;
    GLboolean right;
    GLboolean left;
};

// Default values
const float YAW = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV        =  45.0f;
const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
glm::vec3 Position;
glm::vec3 Front;
glm::vec3 Up;
glm::vec3 Right;
glm::vec3 WorldUp;

// Camera movement direction.
glm::vec3 Dir;

float Yaw;
float Pitch;

float MovementSpeed;
float MouseSensitivity;
float Fov;

Camera_Mode Mode;
Camera_State State;


Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float iFov = FOV, float yaw = YAW, float pitch = PITCH, Camera_Mode iMode = FLY);

Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float iFov = FOV, float yaw = YAW, float pitch = PITCH, Camera_Mode iMode = FLY);

glm::mat4 getViewMatrix();

void processKeyboard(Camera_Movement direction, GLboolean moveOrStop);

void move(float deltaTime);

// constrainPitch sets wheter pitch should be limited to prevent the screen from flipping.
void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

void processMouseScroll(float yOffset);

float getFovRads();

private:

void updateCameraVectors();
};

#endif