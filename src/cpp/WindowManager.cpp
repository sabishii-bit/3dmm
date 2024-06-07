#include "WindowManager.h"

// Function to handle GLFW errors
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

// Function to check OpenGL errors
void checkOpenGLError(const std::string& context)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error (" << context << "): " << err << std::endl;
    }
}

WindowManager* WindowManager::instance = nullptr;
std::once_flag WindowManager::initInstanceFlag;

WindowManager& WindowManager::getInstance()
{
    std::call_once(initInstanceFlag, []()
        {
            instance = new WindowManager(800, 600, "");
        });
    return *instance;
}

WindowManager::WindowManager(int width, int height, const char* title)
    : window(nullptr), width(width), height(height), title(title), renderer(Renderer::getInstance())
{
    if (!initialize())
    {
        throw std::runtime_error("WindowManager failed to initialize.");
    }

    run();
}

WindowManager::~WindowManager()
{
    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

bool WindowManager::initialize()
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return false;
    }

    // Initialize GUI
    gui = std::make_unique<GUI>(window);

    // Initialize InputHandler with GUI
    InputHandler::getInstance().initialize(window, gui.get());

    try
    {
        renderer.initialize(width, height);
        // renderer.createAndAddObject("cube");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Renderer initialization failed: " << e.what() << std::endl;
        return false;
    }

    std::cout << "WindowManager initialized successfully" << std::endl;
    return true;
}

void WindowManager::run()
{
    std::cout << "Entering render loop" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // Handle window events

        float currentFrame = glfwGetTime();
        static float lastFrame = 0.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputHandler::getInstance().processInput(deltaTime);

        clearScreen();

        // Render objects
        renderer.render();

        // Render the ImGui toolbar
        gui->ToolbarComponent();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Check for OpenGL errors
        checkOpenGLError("render loop");
    }
    std::cout << "Exiting render loop" << std::endl;
}

void WindowManager::clearScreen()
{
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
