#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mutex>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    static Camera& getInstance();

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void reset();

private:
    Camera(glm::vec3 position = glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = -20.0f);

    static Camera* instance;
    static std::once_flag initInstanceFlag;

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    // Default camera positioning:
    const glm::vec3 defaultPosition = glm::vec3(0.0f, 2.0f, 5.0f);
    const glm::vec3 defaultUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const float defaultYaw = -90.0f;
    const float defaultPitch = -20.0f;

    float MovementSpeed;
    float MouseSensitivity;

    void updateCameraVectors();
};
