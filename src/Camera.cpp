#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float iFov, float yaw, float pitch, Camera_Mode iMode) : State()
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    Front = glm::vec3(0.0f, 1.0f, 0.0f);
    Dir = Front;
    Fov = iFov;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Mode = iMode;

    updateCameraVectors();
};

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,  float iFov, float yaw, float pitch, Camera_Mode iMode) : State()
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Fov = iFov;
    Front = glm::vec3(0.0f, 1.0f, 0.0f);
    Dir = Front;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Mode = iMode;

    updateCameraVectors();
};

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
};

void Camera::processKeyboard(Camera_Movement direction, GLboolean moveOrStop)
{
    switch (direction) {
        case FORWARD:
            State.forward = moveOrStop;
            break;
        case BACKWARD:
            State.backward = moveOrStop;
            break;
        case LEFT:
            State.left = moveOrStop;
            break;
        case RIGHT:
            State.right = moveOrStop;
            break;
        default:
            break;
    }
};

void Camera::move(float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    
    if (State.forward)
        Position += Dir * velocity;

    if (State.backward)
        Position -= Dir * velocity;
    
    if (State.left)
        Position -= Right * velocity;

    if (State.right)
        Position += Right * velocity;
};

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;

    if (constrainPitch)
    {
        Pitch = glm::min(glm::max(Pitch + yOffset, -89.0f), 89.0f);
    }
    else {
        Pitch += yOffset;
    }

    updateCameraVectors();
};

void Camera::processMouseScroll(float yOffset)
{
    Fov -= glm::min(glm::max(1.0f, Fov - yOffset), 120.0f);
};

float Camera::getFovRads()
{
    return glm::radians(Fov);
};

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    newFront.y = sin(glm::radians(Pitch));
    newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(newFront);

    switch (Mode) {
        case FLY: // Camera flyes around freely
            Dir = Front;
            break;
        case WALK: // Camera moves in the xy-plane
            // Project Front onto the xy plane.
            // UP is ther normal of the plane.
            Dir = glm::normalize(Front - glm::dot(Front, UP)*UP);
            break;
        default:
            Dir = Front;
            break;
    }

    Right = glm::normalize(glm::cross(Dir, WorldUp));
    Up = glm::normalize(glm::cross(Right, Dir));
};