#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "IDGenerator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Object3D
{
public:
    Object3D(const std::vector<float>& vertices);
    virtual ~Object3D();

    GLuint getVAO() const { return vao; }
    GLuint getVBO() const { return vbo; }
    const std::vector<float>& getVertices() const { return vertices; }

    void setPosition(const glm::vec3& position);
    void setScale(const glm::vec3& scale);
    void setRotation(const glm::vec3& rotation);

    glm::mat4 getModelMatrix() const;
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getScale() const { return scale; }
    glm::vec3 getRotation() const { return rotation; }
    const std::string& getID() const { return ID; }

protected:

    std::vector<float> vertices;
    GLuint vao;
    GLuint vbo;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    void setupMesh();
    const std::string ID;
};

class Pyramid : public Object3D
{
public:
    Pyramid(const glm::vec3& colorBase = glm::vec3(1.0f, 0.0f, 0.0f), // Red
        const glm::vec3& colorSide1 = glm::vec3(0.0f, 1.0f, 0.0f), // Green
        const glm::vec3& colorSide2 = glm::vec3(0.0f, 0.0f, 1.0f), // Blue
        const glm::vec3& colorSide3 = glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
        const glm::vec3& colorSide4 = glm::vec3(0.0f, 1.0f, 1.0f)); // Cyan

    void setColorBase(const glm::vec3& color);
    void setColorSide1(const glm::vec3& color);
    void setColorSide2(const glm::vec3& color);
    void setColorSide3(const glm::vec3& color);
    void setColorSide4(const glm::vec3& color);

    glm::vec3 getColorBase() const { return colorBase; }
    glm::vec3 getColorSide1() const { return colorSide1; }
    glm::vec3 getColorSide2() const { return colorSide2; }
    glm::vec3 getColorSide3() const { return colorSide3; }
    glm::vec3 getColorSide4() const { return colorSide4; }

private:
    glm::vec3 colorBase, colorSide1, colorSide2, colorSide3, colorSide4;
    void updateColors();
};

class Cube : public Object3D
{
public:
    Cube(const glm::vec3& colorBottom = glm::vec3(1.0f, 0.0f, 0.0f), // Red
        const glm::vec3& colorTop = glm::vec3(0.0f, 1.0f, 0.0f),    // Green
        const glm::vec3& colorLeft = glm::vec3(0.0f, 0.0f, 1.0f),   // Blue
        const glm::vec3& colorRight = glm::vec3(1.0f, 1.0f, 0.0f),  // Yellow
        const glm::vec3& colorBack = glm::vec3(0.0f, 1.0f, 1.0f),   // Cyan
        const glm::vec3& colorFront = glm::vec3(1.0f, 0.0f, 1.0f)); // Magenta

    void setColorBottom(const glm::vec3& color);
    void setColorTop(const glm::vec3& color);
    void setColorLeft(const glm::vec3& color);
    void setColorRight(const glm::vec3& color);
    void setColorBack(const glm::vec3& color);
    void setColorFront(const glm::vec3& color);

    glm::vec3 getColorBottom() const { return colorBottom; }
    glm::vec3 getColorTop() const { return colorTop; }
    glm::vec3 getColorLeft() const { return colorLeft; }
    glm::vec3 getColorRight() const { return colorRight; }
    glm::vec3 getColorBack() const { return colorBack; }
    glm::vec3 getColorFront() const { return colorFront; }

private:
    glm::vec3 colorBottom, colorTop, colorLeft, colorRight, colorBack, colorFront;
    void updateColors();
};

class Sphere : public Object3D 
{
public:
    Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));
};

class CoordinateAxes : public Object3D
{
public:
    CoordinateAxes();
};

class CheckeredPlane : public Object3D
{
public:
    CheckeredPlane(int gridSize = 10, float spacing = 1.0f);
};


class ObjectFactory 
{
public:
    static std::unique_ptr<Object3D> createObject(const std::string& type);
};