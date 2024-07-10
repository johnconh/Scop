/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-18 16:54:18 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-18 16:54:18 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/Shader.h"


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

    GLint result = GL_FALSE;
    int logLength;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(logLength + 1);
        glGetShaderInfoLog(vertexShader, logLength, NULL, &vertexShaderErrorMessage[0]);
        std::cerr << &vertexShaderErrorMessage[0] << std::endl;
    }

    std::string fragmentShaderSource = readShaderFile(fragmentFilePath);
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(logLength + 1);
        glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cerr << &fragmentShaderErrorMessage[0] << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        std::vector<char> programErrorMessage(logLength + 1);
        glGetProgramInfoLog(shaderProgram, logLength, NULL, &programErrorMessage[0]);
        std::cerr << &programErrorMessage[0] << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}