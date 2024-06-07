#include "ShaderManager.h"

ShaderManager::ShaderManager(const char* vertexPath, const char* fragmentPath) : ID(0)
{
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    GLuint vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

    linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "ShaderManager constructed with ID: " << ID << std::endl;
}

ShaderManager::ShaderManager(const char* vertexSource, const char* fragmentSource, bool isRawSource) : ID(0)
{
    if (isRawSource)
    {
        GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

        linkProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    else
    {
        std::string vertexCode = readShaderFile(vertexSource);
        std::string fragmentCode = readShaderFile(fragmentSource);

        GLuint vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

        linkProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    std::cout << "ShaderManager constructed with ID: " << ID << std::endl;
}

ShaderManager::~ShaderManager()
{
    if (ID != 0)
    {
        glDeleteProgram(ID);
    }
}

void ShaderManager::use()
{
    if (ID != 0)
    {
        glUseProgram(ID);
    }
    else
    {
        std::cerr << "ERROR::SHADER::USE::PROGRAM_NOT_INITIALIZED\n";
    }
}

std::string ShaderManager::readShaderFile(const char* shaderPath)
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(shaderPath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    return shaderStream.str();
}

GLuint ShaderManager::compileShader(const char* shaderCode, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

void ShaderManager::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    ID = glCreateProgram();
    if (ID == 0)
    {
        std::cerr << "ERROR::SHADER::PROGRAM_CREATION_FAILED\n";
        return;
    }
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        ID = 0;  // Ensure ID is zero if linking failed
    }
}


void ShaderManager::setUniform(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::setUniform(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::setUniform(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderManager::setUniform(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
