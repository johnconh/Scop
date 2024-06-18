/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 18:00:01 by jdasilva          #+#    #+#             */
/*   Updated: 2024-06-13 18:00:01 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include  "../inc/glm/glm.hpp"
#include  "../inc/glm/gtc/matrix_transform.hpp"
#include  "../inc/glm/gtc/type_ptr.hpp"
#include <iostream>
#include "../inc/objloader.h"
#include "../inc/checkGLError.h"
#include "../inc/Shader.h"
#include <iomanip>

const GLuint WIDTH = 800, HEIGHT = 600;
void checkGLError()
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <obj file>" << std::endl;
        return -1;
    }

    std::string objFile = argv[1];
    if(objFile.substr(objFile.find_last_of(".") + 1) != "obj")
    {
        std::cerr << "Invalid file format. Please provide a .obj file" << std::endl;
        return -1;
    }

    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if(!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
    const GLubyte *glewVersion = glewGetString(GLEW_VERSION);
    std::cout << "GLEW version: " << glewVersion << std::endl;

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    loadOBJ(objFile.c_str(), vertices, faces);
    std::vector<float> vertexData;
    std::vector<float> colorData;
    for(size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++)
    {
        const Face& face = faces[faceIndex];

        float r = static_cast <float> (faceIndex % 3 == 0);
        float g = static_cast <float> (faceIndex % 3 == 1);
        float b = static_cast <float> (faceIndex % 3 == 2);
    
        for(size_t i = 0; i < face.v.size() - 2; i++)
        {
            vertexData.push_back(vertices[face.v[0] - 1].x);
            vertexData.push_back(vertices[face.v[0] - 1].y);
            vertexData.push_back(vertices[face.v[0] - 1].z);
            colorData.push_back(r);
            colorData.push_back(g);
            colorData.push_back(b);

            vertexData.push_back(vertices[face.v[i + 1] - 1].x);
            vertexData.push_back(vertices[face.v[i + 1] - 1].y);
            vertexData.push_back(vertices[face.v[i + 1] - 1].z);
            colorData.push_back(r);
            colorData.push_back(g);
            colorData.push_back(b);

            vertexData.push_back(vertices[face.v[i + 2] - 1].x);
            vertexData.push_back(vertices[face.v[i + 2] - 1].y);
            vertexData.push_back(vertices[face.v[i + 2] - 1].z);
            colorData.push_back(r);
            colorData.push_back(g);
            colorData.push_back(b);
        }
    }

    GLuint shaderProgram = createShaderProgram("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");

    GLuint VBO[2], VAO;
    CHECK_GL_ERROR(glGenVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glGenBuffers(2, VBO));

    CHECK_GL_ERROR(glBindVertexArray(VAO));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[0]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[1]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(float), colorData.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    CHECK_GL_ERROR(glBindVertexArray(0));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 model = glm::mat4(1.0f);

    while(!glfwWindowShouldClose(window))
    {
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT));

        CHECK_GL_ERROR(glUseProgram(shaderProgram));

        model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

        if (modelLoc == -1 || viewLoc == -1 || projLoc == -1) 
        {
            std::cerr << "Error: Failed to get uniform locations" << std::endl;
            return -1;
        }

        CHECK_GL_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
        CHECK_GL_ERROR(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
        CHECK_GL_ERROR(glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)));

        CHECK_GL_ERROR(glBindVertexArray(VAO));
        CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 3));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    CHECK_GL_ERROR(glDeleteVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glDeleteBuffers(2, VBO));
    CHECK_GL_ERROR(glDeleteProgram(shaderProgram));
    glfwTerminate();
    return 0;
}