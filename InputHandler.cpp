#include "InputHandler.h"

InputHandler* InputHandler::instance = nullptr;
std::once_flag InputHandler::initInstanceFlag;

InputHandler& InputHandler::getInstance()
{
    std::call_once(initInstanceFlag, []()
        {
            instance = new InputHandler();
        });
    return *instance;
}

InputHandler::InputHandler() :
    leftMouseButtonPressed(false), firstMouse(true)
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::initialize(GLFWwindow* window, GUI* gui)
{
    this->gui = gui;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void InputHandler::processInput(float deltaTime)
{
    processKeyInput(deltaTime);

    GLFWwindow* window = glfwGetCurrentContext();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    processMouseInput(static_cast<float>(xpos), static_cast<float>(ypos));

    for (auto& key : keyPressed)
    {
        key.second = false; // Reset key pressed states after processing
    }
}

void InputHandler::processKeyInput(float deltaTime)
{
    Camera& camera = Camera::getInstance();
    if (isKeyHeld(GLFW_KEY_W))
        camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (isKeyHeld(GLFW_KEY_S))
        camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (isKeyHeld(GLFW_KEY_A))
        camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
    if (isKeyHeld(GLFW_KEY_D))
        camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (isKeyPressed(GLFW_KEY_T))
        Renderer::getInstance().toggleWireframe();
}

void InputHandler::processMouseInput(float xpos, float ypos)
{
    if (gui->getIO().WantCaptureMouse) {
        return; // Skip processing if ImGui is capturing the mouse
    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (leftMouseButtonPressed)
    {
        Camera::getInstance().processMouseMovement(xoffset, yoffset);
    }
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputHandler& instance = InputHandler::getInstance();
    if (instance.gui)
    {
        instance.gui->keyCallback(window, key, scancode, action, mods);
    }

    std::cout << "Key callback: key=" << key << ", action=" << action << std::endl;

    if (action == GLFW_PRESS)
    {
        instance.keyStates[key] = true;
        instance.keyPressed[key] = true; // Register the key as just pressed
    }
    else if (action == GLFW_RELEASE)
    {
        instance.keyStates[key] = false;
    }
}

void InputHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputHandler& instance = InputHandler::getInstance();
    if (instance.gui)
    {
        instance.gui->mouseCallback(window, xpos, ypos);
    }

    std::cout << "Mouse callback: xpos=" << xpos << ", ypos=" << ypos << std::endl;
    instance.processMouseInput(static_cast<float>(xpos), static_cast<float>(ypos));
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    InputHandler& instance = InputHandler::getInstance();
    if (instance.gui)
    {
        instance.gui->mouseButtonCallback(window, button, action, mods);
    }

    if (instance.gui->getIO().WantCaptureMouse)
    {
        return; // Skip processing if ImGui is capturing the mouse
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            instance.leftMouseButtonPressed = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            instance.selectObject(static_cast<float>(xpos), static_cast<float>(ypos)); // Handle object selection
        }
        else if (action == GLFW_RELEASE)
        {
            instance.leftMouseButtonPressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}


bool InputHandler::isKeyHeld(int key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputHandler::isKeyPressed(int key) const
{
    auto it = keyPressed.find(key);
    return it != keyPressed.end() && it->second;
}

bool rayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const glm::vec3& minAABB, const glm::vec3& maxAABB)
{
    float tmin = (minAABB.x - rayOrigin.x) / rayDirection.x;
    float tmax = (maxAABB.x - rayOrigin.x) / rayDirection.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (minAABB.y - rayOrigin.y) / rayDirection.y;
    float tymax = (maxAABB.y - rayOrigin.y) / rayDirection.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (minAABB.z - rayOrigin.z) / rayDirection.z;
    float tzmax = (maxAABB.z - rayOrigin.z) / rayDirection.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;
}

void InputHandler::selectObject(float xpos, float ypos)
{
    // Convert screen coordinates to normalized device coordinates (NDC)
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    float x = (2.0f * xpos) / width - 1.0f;
    float y = 1.0f - (2.0f * ypos) / height;

    // Create a ray from the camera into the scene
    glm::vec4 ray_clip = glm::vec4(x, y, -1.0f, 1.0f);
    glm::vec4 ray_eye = glm::inverse(Renderer::getInstance().getProjectionMatrix()) * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;

    glm::vec3 ray_wor = glm::vec3(glm::inverse(Camera::getInstance().getViewMatrix()) * ray_eye);
    ray_wor = glm::normalize(ray_wor);

    glm::vec3 ray_origin = Camera::getInstance().getPosition();

    auto objects = Renderer::getInstance().getObjects();
    for (const auto& object : objects)
    {
        glm::vec3 minAABB = object->getPosition() - glm::vec3(0.5f);
        glm::vec3 maxAABB = object->getPosition() + glm::vec3(0.5f);

        std::cout << "Checking object at position: " << object->getPosition().x << ", " << object->getPosition().y << ", " << object->getPosition().z << std::endl;

        if (rayIntersectsAABB(ray_origin, ray_wor, minAABB, maxAABB))
        {
            std::cout << "Object selected: " << object->getID() << std::endl;
            // Update GUI with object information
            gui->setSelectedObject(object);
            break;
        }
    }
}


