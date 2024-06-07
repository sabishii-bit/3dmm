#include "GraphicsObjects.h"

Sphere::Sphere(float radius, int sectorCount, int stackCount, const glm::vec3& color)
    : Object3D({})
{
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * std::cos(stackAngle);           // r * cos(u)
        z = radius * std::sin(stackAngle);            // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;             // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * std::cos(sectorAngle);           // r * cos(u) * cos(v)
            y = xy * std::sin(sectorAngle);           // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);

            // vertex color (r, g, b)
            vertices.push_back(color.r);
            vertices.push_back(color.g);
            vertices.push_back(color.b);
        }
    }

    // indices
    unsigned int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    // combine vertices, normals, and colors into one vector
    std::vector<float> combinedVertices;
    for (size_t i = 0; i < vertices.size() / 3; ++i)
    {
        combinedVertices.push_back(vertices[i * 3]);
        combinedVertices.push_back(vertices[i * 3 + 1]);
        combinedVertices.push_back(vertices[i * 3 + 2]);
        combinedVertices.push_back(normals[i * 3]);
        combinedVertices.push_back(normals[i * 3 + 1]);
        combinedVertices.push_back(normals[i * 3 + 2]);
        combinedVertices.push_back(vertices[i * 3 + 3]);
        combinedVertices.push_back(vertices[i * 3 + 4]);
        combinedVertices.push_back(vertices[i * 3 + 5]);
    }

    this->vertices = combinedVertices;
    setupMesh();
}