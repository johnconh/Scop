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
#include <iostream>
#include "../inc/objloader.h"
#include "../inc/checkGLError.h"
#include "../inc/Shader.h"
#include "../inc/computeNormals.h"
#include "../inc/Matrix.h"
#include "../inc/Input.h"
#include "../inc/Texture.h"

const GLuint WIDTH = 1080, HEIGHT = 720;
float mixfactor = 0.0f;
bool useTexture = false;
bool useColor = false;
bool wireframeMode = false;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <obj file>" << std::endl;
        return -1;
    }

    std::string objFile = argv[1];
    size_t pos = objFile.find(".");
    if(pos == std::string::npos || objFile.substr(pos) != ".obj")
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
    Material materials;
    loadOBJ(objFile.c_str(), vertices, faces, materials);

    std::vector<Vertex> normalizedVertex;
    computeNormals(vertices, normalizedVertex);

    std::vector<Vector2> uvs = generateUV(vertices, Vector3(1,0,1), Vector3(0,0,0));

    std::vector<float> vertexData;
    std::vector<float> colorData;
    std::vector<float> normals;
    std::vector<float> textureData;

    for(size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++)
    {
        const Face &face = faces[faceIndex];
        float gray = static_cast<float>(faceIndex) / static_cast<float>(faces.size());

        for(size_t i = 0; i < face.v.size() - 2; i++)
        {
            vertexData.push_back(vertices[face.v[0] - 1].x);
            vertexData.push_back(vertices[face.v[0] - 1].y);
            vertexData.push_back(vertices[face.v[0] - 1].z);
            normals.push_back(normalizedVertex[face.v[0] - 1].x);
            normals.push_back(normalizedVertex[face.v[0] - 1].y);
            normals.push_back(normalizedVertex[face.v[0] - 1].z);
            colorData.push_back(gray);
            colorData.push_back(gray);
            colorData.push_back(gray);
            textureData.push_back(uvs[face.v[0] - 1].x);
            textureData.push_back(uvs[face.v[0] - 1].y);

            vertexData.push_back(vertices[face.v[i + 1] - 1].x);
            vertexData.push_back(vertices[face.v[i + 1] - 1].y);
            vertexData.push_back(vertices[face.v[i + 1] - 1].z);
            normals.push_back(normalizedVertex[face.v[i + 1] - 1].x);
            normals.push_back(normalizedVertex[face.v[i + 1] - 1].y);
            normals.push_back(normalizedVertex[face.v[i + 1] - 1].z);
            colorData.push_back(gray);
            colorData.push_back(gray);
            colorData.push_back(gray);
            textureData.push_back(uvs[face.v[i + 1] -1].x);
            textureData.push_back(uvs[face.v[i + 1] - 1].y);

            vertexData.push_back(vertices[face.v[i + 2] - 1].x);
            vertexData.push_back(vertices[face.v[i + 2] - 1].y);
            vertexData.push_back(vertices[face.v[i + 2] - 1].z);
            normals.push_back(normalizedVertex[face.v[i + 2] - 1].x);
            normals.push_back(normalizedVertex[face.v[i + 2] - 1].y);
            normals.push_back(normalizedVertex[face.v[i + 2] - 1].z);
            colorData.push_back(gray);
            colorData.push_back(gray);
            colorData.push_back(gray);
            textureData.push_back(uvs[face.v[i + 2] - 1].x);
            textureData.push_back(uvs[face.v[i + 2] - 1].y);
        }
    }
    // for(size_t i = 0; i < vertexData.size(); i += 3) {
    //     std::cout << "Vertex " << (i/3) + 1 << ": (" << vertexData[i] << ", " << vertexData[i+1] << ", " << vertexData[i+2] << ")" << std::endl;
    // }

    GLuint shaderProgram = createShaderProgram("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
    GLuint textureID = loadTexture("res/textures/img.bmp");

    GLuint VBO[4], VAO;
    CHECK_GL_ERROR(glGenVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glGenBuffers(4, VBO));

    CHECK_GL_ERROR(glBindVertexArray(VAO));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[0]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[1]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(float), colorData.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[2]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(2));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO[3]));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, textureData.size() * sizeof(float), textureData.data(), GL_STATIC_DRAW));
    CHECK_GL_ERROR(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(3));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    CHECK_GL_ERROR(glBindVertexArray(0));

    Vector3 lightPos({1.2f, 1.0f, 10.0f});
    Vector3 cameraPos({0.0f, 0.0f, 10.0f});
    Matrix4 projection = perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    Matrix4 view = lookAt(cameraPos, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    Matrix4 model = identity();
    Vector3 OBJcenter = calculateObjectCenter(vertices);

    float rotationSpeed = 1.0f;
    double lastFrameTime = static_cast<float>(glfwGetTime());

    Vector3 objectMovement = {0.0f, 0.0f, 0.0f};
    float movementSpeed = 0.05f;

    while(!glfwWindowShouldClose(window))
    {
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
        CHECK_GL_ERROR(glDepthFunc(GL_LESS));

        CHECK_GL_ERROR(glUseProgram(shaderProgram));

        double currenTime = static_cast<float>(glfwGetTime());
        double deltaTime = currenTime - lastFrameTime;
        lastFrameTime = currenTime;

        handleInput(window, model, objectMovement, movementSpeed, deltaTime, useTexture, wireframeMode);
        handleColor(window, VBO[1], faces, colorData, useColor);
        handleCameraMove(window, cameraPos);
        view = lookAt(cameraPos, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});

        float deltaAngle = rotationSpeed * deltaTime;
        model = rotateAroundCenter(model, deltaAngle, {0.0f, 1.0f, 0.0f}, OBJcenter);
        
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");

        CHECK_GL_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.m[0][0]));
        CHECK_GL_ERROR(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view.m[0][0]));
        CHECK_GL_ERROR(glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection.m[0][0]));
        CHECK_GL_ERROR(glUniform3fv(lightPosLoc, 1, &lightPos.x));
        CHECK_GL_ERROR(glUniform3fv(viewPosLoc, 1, &cameraPos.x));

        GLint matKdLoc = glGetUniformLocation(shaderProgram, "material.Kd");
        GLint matKsLoc = glGetUniformLocation(shaderProgram, "material.Ks");
        GLint matKaLoc = glGetUniformLocation(shaderProgram, "material.Ka");
        GLint matNsLoc = glGetUniformLocation(shaderProgram, "material.Ns");
        GLint matNiLoc = glGetUniformLocation(shaderProgram, "material.Ni");
        GLint matDLoc = glGetUniformLocation(shaderProgram, "material.d");
        GLint matIllumLoc = glGetUniformLocation(shaderProgram, "material.illum");

        CHECK_GL_ERROR(glUniform3fv(matKdLoc, 1, &materials.Kd.x));
        CHECK_GL_ERROR(glUniform3fv(matKsLoc, 1, &materials.Ks.x));
        CHECK_GL_ERROR(glUniform3fv(matKaLoc, 1, &materials.Ka.x));
        CHECK_GL_ERROR(glUniform1f(matNsLoc, materials.Ns));
        CHECK_GL_ERROR(glUniform1f(matNiLoc, materials.Ni));
        CHECK_GL_ERROR(glUniform1f(matDLoc, materials.d));
        CHECK_GL_ERROR(glUniform1i(matIllumLoc, materials.illum));

        CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0));
        CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, textureID));
        glUniform1f(glGetUniformLocation(shaderProgram, "mixFactor"), useTexture ? 1.0f : 0.0f);

        CHECK_GL_ERROR(glBindVertexArray(VAO));
        CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 3));

        glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    CHECK_GL_ERROR(glDeleteVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glDeleteBuffers(4, VBO));
    CHECK_GL_ERROR(glDeleteProgram(shaderProgram));
    glfwTerminate();
    return 0;
}