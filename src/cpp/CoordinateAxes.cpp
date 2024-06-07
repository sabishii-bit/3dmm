#include "GraphicsObjects.h"

CoordinateAxes::CoordinateAxes() : Object3D({
    // X axis (red)
    0.0f, 0.01f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.01f, 0.0f, 1.0f, 0.0f, 0.0f,

    // Y axis (green)
    0.0f, 0.01f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.01f, 0.0f, 0.0f, 1.0f, 0.0f,

    // Z axis (blue)
    0.0f, 0.01f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.01f, 1.0f, 0.0f, 0.0f, 1.0f
    })
{
    setupMesh();
}
