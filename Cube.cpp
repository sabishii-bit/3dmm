#include "GraphicsObjects.h"

Cube::Cube(const glm::vec3& colorBottom, const glm::vec3& colorTop, const glm::vec3& colorLeft,
    const glm::vec3& colorRight, const glm::vec3& colorBack, const glm::vec3& colorFront)
    : Object3D({
    // Bottom face
    -0.5f, 0.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
     0.5f, 0.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
     0.5f, 1.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
     0.5f, 1.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
    -0.5f, 1.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
    -0.5f, 0.0f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,

    // Top face
    -0.5f, 0.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,
     0.5f, 0.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,
     0.5f, 1.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,
     0.5f, 1.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,
    -0.5f, 1.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,
    -0.5f, 0.0f, 0.5f, colorTop.r, colorTop.g, colorTop.b,

    // Left face
    -0.5f, 1.0f, 0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
    -0.5f, 1.0f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
    -0.5f, 0.0f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
    -0.5f, 0.0f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
    -0.5f, 0.0f, 0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
    -0.5f, 1.0f, 0.5f, colorLeft.r, colorLeft.g, colorLeft.b,

    // Right face
     0.5f, 1.0f, 0.5f, colorRight.r, colorRight.g, colorRight.b,
     0.5f, 1.0f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
     0.5f, 0.0f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
     0.5f, 0.0f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
     0.5f, 0.0f, 0.5f, colorRight.r, colorRight.g, colorRight.b,
     0.5f, 1.0f, 0.5f, colorRight.r, colorRight.g, colorRight.b,

     // Back face
     -0.5f, 0.0f, -0.5f, colorBack.r, colorBack.g, colorBack.b,
      0.5f, 0.0f, -0.5f, colorBack.r, colorBack.g, colorBack.b,
      0.5f, 0.0f, 0.5f, colorBack.r, colorBack.g, colorBack.b,
      0.5f, 0.0f, 0.5f, colorBack.r, colorBack.g, colorBack.b,
     -0.5f, 0.0f, 0.5f, colorBack.r, colorBack.g, colorBack.b,
     -0.5f, 0.0f, -0.5f, colorBack.r, colorBack.g, colorBack.b,

     // Front face
     -0.5f, 1.0f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
      0.5f, 1.0f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
      0.5f, 1.0f, 0.5f, colorFront.r, colorFront.g, colorFront.b,
      0.5f, 1.0f, 0.5f, colorFront.r, colorFront.g, colorFront.b,
     -0.5f, 1.0f, 0.5f, colorFront.r, colorFront.g, colorFront.b,
     -0.5f, 1.0f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
        }),
        colorBottom(colorBottom),
        colorTop(colorTop),
        colorLeft(colorLeft),
        colorRight(colorRight),
        colorBack(colorBack),
        colorFront(colorFront)
{
    setupMesh();
}


void Cube::setColorBottom(const glm::vec3& color) { colorBottom = color; updateColors(); }
void Cube::setColorTop(const glm::vec3& color) { colorTop = color; updateColors(); }
void Cube::setColorLeft(const glm::vec3& color) { colorLeft = color; updateColors(); }
void Cube::setColorRight(const glm::vec3& color) { colorRight = color; updateColors(); }
void Cube::setColorBack(const glm::vec3& color) { colorBack = color; updateColors(); }
void Cube::setColorFront(const glm::vec3& color) { colorFront = color; updateColors(); }

void Cube::updateColors() {
    vertices = {
        // Bottom face
        -0.5f, -0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
         0.5f, -0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
         0.5f,  0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
         0.5f,  0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
        -0.5f,  0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,
        -0.5f, -0.5f, -0.5f, colorBottom.r, colorBottom.g, colorBottom.b,

        // Top face
        -0.5f, -0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,
         0.5f, -0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,
         0.5f,  0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,
         0.5f,  0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,
        -0.5f,  0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,
        -0.5f, -0.5f,  0.5f, colorTop.r, colorTop.g, colorTop.b,

        // Left face
        -0.5f,  0.5f,  0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
        -0.5f,  0.5f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
        -0.5f, -0.5f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
        -0.5f, -0.5f, -0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
        -0.5f, -0.5f,  0.5f, colorLeft.r, colorLeft.g, colorLeft.b,
        -0.5f,  0.5f,  0.5f, colorLeft.r, colorLeft.g, colorLeft.b,

        // Right face
         0.5f,  0.5f,  0.5f, colorRight.r, colorRight.g, colorRight.b,
         0.5f,  0.5f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
         0.5f, -0.5f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
         0.5f, -0.5f, -0.5f, colorRight.r, colorRight.g, colorRight.b,
         0.5f, -0.5f,  0.5f, colorRight.r, colorRight.g, colorRight.b,
         0.5f,  0.5f,  0.5f, colorRight.r, colorRight.g, colorRight.b,

         // Back face
         -0.5f, -0.5f, -0.5f, colorBack.r, colorBack.g, colorBack.b,
          0.5f, -0.5f, -0.5f, colorBack.r, colorBack.g, colorBack.b,
          0.5f, -0.5f,  0.5f, colorBack.r, colorBack.g, colorBack.b,
          0.5f, -0.5f,  0.5f, colorBack.r, colorBack.g, colorBack.b,
         -0.5f, -0.5f,  0.5f, colorBack.r, colorBack.g, colorBack.b,
         -0.5f, -0.5f, -0.5f, colorBack.r, colorBack.g, colorBack.b,

         // Front face
         -0.5f,  0.5f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
          0.5f,  0.5f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
          0.5f,  0.5f,  0.5f, colorFront.r, colorFront.g, colorFront.b,
          0.5f,  0.5f,  0.5f, colorFront.r, colorFront.g, colorFront.b,
         -0.5f,  0.5f,  0.5f, colorFront.r, colorFront.g, colorFront.b,
         -0.5f,  0.5f, -0.5f, colorFront.r, colorFront.g, colorFront.b,
    };
    setupMesh();
}

