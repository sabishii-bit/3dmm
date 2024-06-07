#include "GraphicsObjects.h"

Pyramid::Pyramid(const glm::vec3& colorBase, const glm::vec3& colorSide1, const glm::vec3& colorSide2,
    const glm::vec3& colorSide3, const glm::vec3& colorSide4)
    : Object3D({
    // Base
    -0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,
     0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,
     0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
     0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
    -0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
    -0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,

    // Side 1
    -0.5f, 0.0f, -0.5f, colorSide1.r, colorSide1.g, colorSide1.b,
     0.5f, 0.0f, -0.5f, colorSide1.r, colorSide1.g, colorSide1.b,
     0.0f, 0.5f,  0.0f, colorSide1.r, colorSide1.g, colorSide1.b,

     // Side 2
      0.5f, 0.0f, -0.5f, colorSide2.r, colorSide2.g, colorSide2.b,
      0.5f, 0.0f,  0.5f, colorSide2.r, colorSide2.g, colorSide2.b,
      0.0f, 0.5f,  0.0f, colorSide2.r, colorSide2.g, colorSide2.b,

      // Side 3
       0.5f, 0.0f,  0.5f, colorSide3.r, colorSide3.g, colorSide3.b,
      -0.5f, 0.0f,  0.5f, colorSide3.r, colorSide3.g, colorSide3.b,
       0.0f, 0.5f,  0.0f, colorSide3.r, colorSide3.g, colorSide3.b,

       // Side 4
       -0.5f, 0.0f,  0.5f, colorSide4.r, colorSide4.g, colorSide4.b,
       -0.5f, 0.0f, -0.5f, colorSide4.r, colorSide4.g, colorSide4.b,
        0.0f, 0.5f,  0.0f, colorSide4.r, colorSide4.g, colorSide4.b
        }),
    colorBase(colorBase),
    colorSide1(colorSide1),
    colorSide2(colorSide2),
    colorSide3(colorSide3),
    colorSide4(colorSide4)
{
    setupMesh();
}

void Pyramid::setColorBase(const glm::vec3& color) { colorBase = color; updateColors(); }
void Pyramid::setColorSide1(const glm::vec3& color) { colorSide1 = color; updateColors(); }
void Pyramid::setColorSide2(const glm::vec3& color) { colorSide2 = color; updateColors(); }
void Pyramid::setColorSide3(const glm::vec3& color) { colorSide3 = color; updateColors(); }
void Pyramid::setColorSide4(const glm::vec3& color) { colorSide4 = color; updateColors(); }

void Pyramid::updateColors() {
    vertices = {
        // Base
        -0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,
         0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,
         0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
         0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
        -0.5f, 0.0f,  0.5f, colorBase.r, colorBase.g, colorBase.b,
        -0.5f, 0.0f, -0.5f, colorBase.r, colorBase.g, colorBase.b,

        // Side 1
        -0.5f, 0.0f, -0.5f, colorSide1.r, colorSide1.g, colorSide1.b,
         0.5f, 0.0f, -0.5f, colorSide1.r, colorSide1.g, colorSide1.b,
         0.0f, 0.5f,  0.0f, colorSide1.r, colorSide1.g, colorSide1.b,

         // Side 2
          0.5f, 0.0f, -0.5f, colorSide2.r, colorSide2.g, colorSide2.b,
          0.5f, 0.0f,  0.5f, colorSide2.r, colorSide2.g, colorSide2.b,
          0.0f, 0.5f,  0.0f, colorSide2.r, colorSide2.g, colorSide2.b,

          // Side 3
           0.5f, 0.0f,  0.5f, colorSide3.r, colorSide3.g, colorSide3.b,
          -0.5f, 0.0f,  0.5f, colorSide3.r, colorSide3.g, colorSide3.b,
           0.0f, 0.5f,  0.0f, colorSide3.r, colorSide3.g, colorSide3.b,

           // Side 4
           -0.5f, 0.0f,  0.5f, colorSide4.r, colorSide4.g, colorSide4.b,
           -0.5f, 0.0f, -0.5f, colorSide4.r, colorSide4.g, colorSide4.b,
            0.0f, 0.5f,  0.0f, colorSide4.r, colorSide4.g, colorSide4.b
    };
    setupMesh();
}
