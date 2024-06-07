#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <memory>
#include <mutex>
#include "Renderer.h"
#include "InputHandler.h"
#include "GUI.h"

class WindowManager
{
public:
    static WindowManager& getInstance();
    ~WindowManager();

    void run();

private:
    WindowManager(int width, int height, const char* title);
    bool initialize();
    void clearScreen();
    void renderToolbar();

    static WindowManager* instance;
    static std::once_flag initInstanceFlag;

    GLFWwindow* window;
    int width;
    int height;
    const char* title;

    Renderer& renderer;
    std::unique_ptr<GUI> gui;
};
