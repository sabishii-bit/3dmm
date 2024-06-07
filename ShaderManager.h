#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ShaderManager
{
public:
    GLuint ID;
    ShaderManager(const char* vertexPath, const char* fragmentPath);
    ShaderManager(const char* vertexSource, const char* fragmentSource, bool isRawSource);
    ~ShaderManager();
    void use();
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

private:
    std::string readShaderFile(const char* shaderPath);
    GLuint compileShader(const char* shaderCode, GLenum shaderType);
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};
