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
    for(const Face& face : faces)
    {
        for(unsigned int v : face.v)
        {
            vertexData.push_back(vertices[v - 1].x);
            vertexData.push_back(vertices[v - 1].y);
            vertexData.push_back(vertices[v - 1].z);
        }
    }

    // std::cout << "First 5 sets of vertex data:" << std::endl;
    // std::cout << std::fixed << std::setprecision(6);
    // for (size_t i = 0; i < 5 * 3 && i < vertexData.size(); i += 3) { // Each vertex has 3 components (x, y, z)
    //     std::cout << "Vertex " << i / 3 << ": ("
    //               << vertexData[i] << ", "
    //               << vertexData[i + 1] << ", "
    //               << vertexData[i + 2] << ")" << std::endl;
    // }

    // // Print first 5 faces and their corresponding vertices for debugging
    // std::cout << "First 5 faces and their corresponding vertices:" << std::endl;
    // for (size_t i = 0; i < 5 && i < faces.size(); ++i) {
    //     const Face& face = faces[i];
    //     std::cout << "Face " << i << ": ";
    //     for (unsigned int index : face.v) {
    //         std::cout << index << " ";
    //     }
    //     std::cout << std::endl;

    //     for (unsigned int index : face.v) {
    //         const Vertex& vertex = vertices[index - 1];
    //         std::cout << "Vertex " << index << ": ("
    //                   << vertex.x << ", "
    //                   << vertex.y << ", "
    //                   << vertex.z << ")" << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    GLuint shaderProgram = createShaderProgram("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");

    GLuint VBO, VAO;
    CHECK_GL_ERROR(glGenVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glGenBuffers(1, &VBO));

    CHECK_GL_ERROR(glBindVertexArray(VAO));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW));

    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    CHECK_GL_ERROR(glBindVertexArray(0));

    
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");

    while(!glfwWindowShouldClose(window))
    {
        float rotationAngle = glfwGetTime();
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT));

        CHECK_GL_ERROR(glBindVertexArray(VAO));
        CHECK_GL_ERROR(glUseProgram(shaderProgram));
        CHECK_GL_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
        CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 3));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    CHECK_GL_ERROR(glDeleteVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glDeleteBuffers(1, &VBO));
    CHECK_GL_ERROR(glDeleteProgram(shaderProgram));
    glfwTerminate();
    return 0;
}