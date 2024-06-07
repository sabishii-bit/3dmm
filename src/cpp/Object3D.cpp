#include "GraphicsObjects.h"

Object3D::Object3D(const std::vector<float>& verts) :
    vertices(verts), vao(0), vbo(0), position(0.0f), scale(1.0f), rotation(0.0f), ID(IDGenerator::generateRandomID())
{
    std::cout << "Creating Object3D with vertices count: " << verts.size() << std::endl;
    setupMesh();
}

Object3D::~Object3D()
{
    std::cout << "Deleting Object3D with VAO: " << vao << std::endl;
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Object3D::setupMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    std::cout << "VAO: " << vao << ", VBO: " << vbo << std::endl;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "Mesh setup completed for VAO: " << vao << std::endl;
}

void Object3D::setPosition(const glm::vec3& pos)
{
    position = pos;
}

void Object3D::setScale(const glm::vec3& scl)
{
    scale = scl;
}

void Object3D::setRotation(const glm::vec3& rot)
{
    rotation = rot;
}

glm::mat4 Object3D::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}
