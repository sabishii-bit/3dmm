#include "Renderer.h"

Renderer* Renderer::instance = nullptr;
std::once_flag Renderer::initInstanceFlag;

Renderer& Renderer::getInstance()
{
    std::call_once(initInstanceFlag, []()
        {
            instance = new Renderer();
        });
    return *instance;
}

Renderer::Renderer() : isWireframe(false)
{
}

Renderer::~Renderer()
{
}

void Renderer::initialize(int width, int height)
{
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColor;

    out vec3 vertexColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        vertexColor = aColor;
    }
    )";

    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(vertexColor, 1.0);
    }
    )";

    colorShader = std::make_unique<ShaderManager>(vertexShaderSource, fragmentShaderSource, true);
    if (colorShader == nullptr || colorShader->ID == 0)
    {
        throw std::runtime_error("Failed to initialize shader program");
    }
    colorShader->use();

    projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    // Initialize coordinate axes
    axes = std::make_unique<CoordinateAxes>();

    // Initialize checkered plane
    plane = std::make_unique<CheckeredPlane>();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    std::cout << "Renderer initialized with shader ID: " << colorShader->ID << std::endl;
}

void Renderer::createAndAddObject(const std::string& type)
{
    std::shared_ptr<Object3D> object = ObjectFactory::createObject(type);
    objects.push_back(object);
    std::cout << "Object of type " << type << " added to renderer with VAO: " << object->getVAO() << std::endl;
}

void Renderer::render()
{
    glm::mat4 view = Camera::getInstance().getViewMatrix();

    colorShader->use();
    colorShader->setUniform("view", view);
    colorShader->setUniform("projection", projection);

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render checkered plane
    colorShader->setUniform("model", plane->getModelMatrix());
    glBindVertexArray(plane->getVAO());
    glDrawArrays(GL_LINES, 0, plane->getVertices().size() / 6);
    glBindVertexArray(0);

    // Render coordinate axes
    colorShader->setUniform("model", glm::mat4(1.0f));
    glBindVertexArray(axes->getVAO());
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);

    // Render objects
    for (const auto& object : objects)
    {
        colorShader->setUniform("model", object->getModelMatrix());
        glBindVertexArray(object->getVAO());
        glDrawArrays(GL_TRIANGLES, 0, object->getVertices().size() / 6); // Ensure vertex count is correct
        glBindVertexArray(0);
    }
}

void Renderer::toggleWireframe()
{
    if (isWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    isWireframe = !isWireframe;
}

std::vector<std::shared_ptr<Object3D>>& Renderer::getObjects()
{
    return objects;
}
