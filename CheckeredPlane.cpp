#include "GraphicsObjects.h"

CheckeredPlane::CheckeredPlane(int gridSize, float spacing)
    : Object3D({})
{
    std::vector<float> vertices;
    for (int i = -gridSize; i <= gridSize; ++i)
    {
        float x = i * spacing;
        float z = i * spacing;

        // Lines parallel to X-axis
        vertices.insert(vertices.end(), 
            {
                x, 0.0f, -gridSize * spacing, 1.0f, 1.0f, 1.0f,
                x, 0.0f,  gridSize * spacing, 1.0f, 1.0f, 1.0f
            });

        // Lines parallel to Z-axis
        vertices.insert(vertices.end(), 
            {
                -gridSize * spacing, 0.0f, z, 1.0f, 1.0f, 1.0f,
                 gridSize * spacing, 0.0f, z, 1.0f, 1.0f, 1.0f
            });
    }

    this->vertices = vertices;
    setupMesh();
}
