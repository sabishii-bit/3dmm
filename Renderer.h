#pragma once

#include <vector>
#include <memory>
#include <string>
#include <mutex>
#include "GraphicsObjects.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <stdexcept>
#include <iostream>

class Renderer {
public:
    static Renderer& getInstance();

    void initialize(int width, int height);
    void render();
    void toggleWireframe();
    void createAndAddObject(const std::string& type);
    std::vector<std::shared_ptr<Object3D>>& getObjects();

    glm::mat4 getProjectionMatrix() const { return projection; }

private:
    Renderer();
    ~Renderer();

    static Renderer* instance;
    static std::once_flag initInstanceFlag;

    std::unique_ptr<ShaderManager> colorShader;
    glm::mat4 projection;
    bool isWireframe;

    std::unique_ptr<CoordinateAxes> axes;
    std::unique_ptr<CheckeredPlane> plane;
    std::vector<std::shared_ptr<Object3D>> objects;
};
