#include "../inc/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string readShaderFile(const char* filePath)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.good())
    {
        std::cerr << "Error: Unable to open shader file " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << fileStream.rdbuf();
    return shaderStream.str();
}   

GLuint createShaderProgram(const char* vertexFilePath, const char* fragmentFilePath)
{
    std::string vertexShaderSource = readShaderFile(vertexFilePath);
    const char* vertexShaderSourceCStr = vertexShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Error compiling vertex shader: " << infoLog << std::endl;
    }

    std::string fragmentShaderSource = readShaderFile(fragmentFilePath);
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Error compiling fragment shader: " << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}