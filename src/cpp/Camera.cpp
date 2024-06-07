#include "Camera.h"

Camera* Camera::instance = nullptr;
std::once_flag Camera::initInstanceFlag;

Camera& Camera::getInstance()
{
    std::call_once(initInstanceFlag, []()
        {
            instance = new Camera();
        });
    return *instance;
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch), MovementSpeed(2.5f), MouseSensitivity(0.1f)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::vec3 Camera::getPosition() const
{
    return Position;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Camera::Yaw += xoffset;
    Camera::Pitch += yoffset;

    if (Camera::Pitch > 89.0f)
        Camera::Pitch = 89.0f;
    if (Camera::Pitch < -89.0f)
        Camera::Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::reset()
{
    Camera::Position = Camera::defaultPosition;
    Camera::Yaw = Camera::defaultYaw;
    Camera::Pitch = Camera::defaultPitch;
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Camera::Yaw)) * cos(glm::radians(Camera::Pitch));
    front.y = sin(glm::radians(Camera::Pitch));
    front.z = sin(glm::radians(Camera::Yaw)) * cos(glm::radians(Camera::Pitch));
    Camera::Front = glm::normalize(front);
    Camera::Right = glm::normalize(glm::cross(Camera::Front, Camera::WorldUp));
    Camera::Up = glm::normalize(glm::cross(Camera::Right, Camera::Front));
}
