#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <GL/glew.h>
#include <string>

std::string readShaderFile(const char* filePath);
GLuint createShaderProgram(const char* vertexFilePath, const char* fragmentFilePath);

#endif
