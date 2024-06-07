#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Camera.h"
#include "Renderer.h"
#include "GraphicsObjects.h"

class GUI
{
public:
    GUI(GLFWwindow* windowContext);
    ~GUI();

    void initialize();
    void beginFrame();
    void endFrame();
    void beginWindow(const std::string& title, const ImVec2& pos = ImVec2(0, 0), const ImVec2& size = ImVec2(0, 0), bool setPos = false, bool setSize = false);
    void endWindow();
    bool addButton(const std::string& label);
    bool addDropdown(const std::string& label, std::vector<std::string>& items, int& currentItem);

    // Event forwarding methods
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void setSelectedObject(std::shared_ptr<Object3D> object);

    // Get ImGui IO for checking input capture
    ImGuiIO& getIO();

    // Specific functions for creating GUI components we'll use
    void ToolbarComponent();

private:
    void clampWindow();

    GLFWwindow* windowContext;

    std::shared_ptr<Object3D> selectedObject;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};
