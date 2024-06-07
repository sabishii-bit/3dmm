#include "GUI.h"

GUI::GUI(GLFWwindow* windowContext) : windowContext(windowContext)
{
    if (!windowContext)
    {
        std::cout << "No window context provided for GUI to sit on." << std::endl;
        return;
    }

    initialize();
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::initialize()
{
    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(windowContext, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::endFrame()
{
    // Rendering
    ImGui::Render();

    // Save the current state of the OpenGL depth test
    GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST); // Disable depth testing for ImGui rendering

    // Render ImGui draw data
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Restore the previous state of the OpenGL depth test
    if (depthTestEnabled)
        glEnable(GL_DEPTH_TEST);
}

void GUI::beginWindow(const std::string& title, const ImVec2& pos, const ImVec2& size, bool setPos, bool setSize)
{
    if (setPos) {
        ImGui::SetNextWindowPos(pos);
    }
    if (setSize) {
        ImGui::SetNextWindowSize(size);
    }

    ImGui::Begin(title.c_str());
    GUI::clampWindow();
}

void GUI::endWindow()
{
    ImGui::End();
}

bool GUI::addButton(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

bool GUI::addDropdown(const std::string& label, std::vector<std::string>& items, int& currentItem)
{
    if (ImGui::BeginCombo(label.c_str(), items[currentItem].c_str()))
    {
        for (int n = 0; n < items.size(); n++)
        {
            bool isSelected = (currentItem == n);
            if (ImGui::Selectable(items[n].c_str(), isSelected))
                currentItem = n;
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
        return true;
    }
    return false;
}

void GUI::clampWindow()
{
    // Define the main application window size
    int display_w, display_h;
    glfwGetFramebufferSize(windowContext, &display_w, &display_h);

    // Get the current position of the ImGui window
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();

    // Clamp the ImGui window position within the application window boundaries
    window_pos.x = std::max(0.0f, std::min(window_pos.x, static_cast<float>(display_w) - window_size.x));
    window_pos.y = std::max(0.0f, std::min(window_pos.y, static_cast<float>(display_h) - window_size.y));
    ImGui::SetWindowPos(window_pos);
}

// Event forwarding methods
void GUI::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void GUI::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void GUI::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

ImGuiIO& GUI::getIO()
{
    return ImGui::GetIO();
}

void GUI::setSelectedObject(std::shared_ptr<Object3D> object)
{
    std::cout << "Object selected: " << object->getID().c_str() << std::endl;
    GUI::selectedObject = object;
}

void GUI::ToolbarComponent()
{
    static std::vector<std::string> shapes = { "cube", "pyramid" };
    static int currentShape = 0;

    ImVec2 pos(5, 5);
    ImVec2 size(215, 425);

    beginFrame();
    beginWindow("Toolbar", pos, size, true, true);

    if (addButton("Reset Camera")) {
        Camera::getInstance().reset();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Select Shape");
    ImGui::Spacing();
    addDropdown("", shapes, currentShape);

    if (addButton("Place Object")) {
        Renderer::getInstance().createAndAddObject(shapes[currentShape]);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (selectedObject) {
        ImGui::Text("Object ID: %s", selectedObject->getID().c_str());

        ImGui::Spacing();

        glm::vec3 position = selectedObject->getPosition();
        glm::vec3 scale = selectedObject->getScale();
        glm::vec3 rotation = selectedObject->getRotation();

        ImGui::Text("Transformations:");
        ImGui::Spacing();

        if (ImGui::InputFloat3("Position", &position[0])) {
            selectedObject->setPosition(position);
        }

        ImGui::Spacing();

        if (ImGui::InputFloat3("Scale", &scale[0])) {
            selectedObject->setScale(scale);
        }

        ImGui::Spacing();

        if (ImGui::InputFloat3("Rotation", &rotation[0])) {
            selectedObject->setRotation(rotation);
        }

        ImGui::Spacing();

        if (auto cube = std::dynamic_pointer_cast<Cube>(selectedObject)) {
            ImGui::Text("Colors:");
            glm::vec3 colorBottom = cube->getColorBottom();
            glm::vec3 colorTop = cube->getColorTop();
            glm::vec3 colorLeft = cube->getColorLeft();
            glm::vec3 colorRight = cube->getColorRight();
            glm::vec3 colorBack = cube->getColorBack();
            glm::vec3 colorFront = cube->getColorFront();

            if (ImGui::ColorEdit3("Bottom", &colorBottom[0])) {
                cube->setColorBottom(colorBottom);
            }
            if (ImGui::ColorEdit3("Top", &colorTop[0])) {
                cube->setColorTop(colorTop);
            }
            if (ImGui::ColorEdit3("Left", &colorLeft[0])) {
                cube->setColorLeft(colorLeft);
            }
            if (ImGui::ColorEdit3("Right", &colorRight[0])) {
                cube->setColorRight(colorRight);
            }
            if (ImGui::ColorEdit3("Back", &colorBack[0])) {
                cube->setColorBack(colorBack);
            }
            if (ImGui::ColorEdit3("Front", &colorFront[0])) {
                cube->setColorFront(colorFront);
            }
        }

        if (auto pyramid = std::dynamic_pointer_cast<Pyramid>(selectedObject)) {
            ImGui::Text("Colors:");
            glm::vec3 colorBase = pyramid->getColorBase();
            glm::vec3 colorSide1 = pyramid->getColorSide1();
            glm::vec3 colorSide2 = pyramid->getColorSide2();
            glm::vec3 colorSide3 = pyramid->getColorSide3();
            glm::vec3 colorSide4 = pyramid->getColorSide4();

            if (ImGui::ColorEdit3("Base", &colorBase[0])) {
                pyramid->setColorBase(colorBase);
            }
            if (ImGui::ColorEdit3("Side1", &colorSide1[0])) {
                pyramid->setColorSide1(colorSide1);
            }
            if (ImGui::ColorEdit3("Side2", &colorSide2[0])) {
                pyramid->setColorSide2(colorSide2);
            }
            if (ImGui::ColorEdit3("Side3", &colorSide3[0])) {
                pyramid->setColorSide3(colorSide3);
            }
            if (ImGui::ColorEdit3("Side4", &colorSide4[0])) {
                pyramid->setColorSide4(colorSide4);
            }
        }
    }

    endWindow();
    endFrame();
}

