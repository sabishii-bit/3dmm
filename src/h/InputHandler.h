#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <glm/gtc/matrix_inverse.hpp>
#include "Camera.h"
#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.h"

class InputHandler
{
public:
    static InputHandler& getInstance();
    ~InputHandler();

    void initialize(GLFWwindow* window, GUI* gui);
    void processInput(float deltaTime);

private:
    InputHandler();

    static InputHandler* instance;
    static std::once_flag initInstanceFlag;

    bool leftMouseButtonPressed;
    bool firstMouse;
    float lastX;
    float lastY;

    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> keyPressed;

    void processKeyInput(float deltaTime);
    void processMouseInput(float xpos, float ypos);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    bool isKeyHeld(int key) const;
    bool isKeyPressed(int key) const;

    GUI* gui; // Pointer to GUI instance

    void selectObject(float xpos, float ypos);
};
