/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 14:28:41 by jdasilva          #+#    #+#             */
/*   Updated: 2024-07-10 14:28:41 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Input.h"

static bool wasTPressed = false;
static bool wasCPressed = false;

void handleInput(GLFWwindow *window, Matrix4& model, Vector3& objectMovement, float movementSpeed, float deltaTime, bool &useTexture)
{
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        objectMovement.z -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, 0.0f, -movementSpeed);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        objectMovement.z += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, 0.0f, movementSpeed);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        objectMovement.x -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(-movementSpeed, 0.0f, 0.0f);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        objectMovement.x += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(movementSpeed, 0.0f, 0.0f);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        objectMovement.y += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, movementSpeed, 0.0f);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        objectMovement.y -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, -movementSpeed, 0.0f);
        model = model * translation;
    }
    if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        if(!wasTPressed)
        {
            wasTPressed = true;
            useTexture = !useTexture;
        }
    }
    else
    {
        wasTPressed = false;
    }
}

void handleColor(GLFWwindow *window, GLuint colorBuffer, const std::vector<Face>& faces, std::vector<float> colorData, bool& useColor)
{
    bool isCPressed = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;

    if (isCPressed && !wasCPressed)
    {
        useColor = !useColor;
        colorData.clear();
        for(size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++)
        {
            const Face &face = faces[faceIndex];
            float r = static_cast <float> (faceIndex % 3 == 0);
            float g = static_cast <float> (faceIndex % 3 == 1);
            float b = static_cast <float> (faceIndex % 3 == 2);
            float gray = static_cast<float>(faceIndex) / static_cast<float>(faces.size());

            for(size_t i = 0; i < face.v.size() - 2; i++)
            {
                if (useColor) {
                    colorData.push_back(r);
                    colorData.push_back(g);
                    colorData.push_back(b);

                    colorData.push_back(r);
                    colorData.push_back(g);
                    colorData.push_back(b);

                    colorData.push_back(r);
                    colorData.push_back(g);
                    colorData.push_back(b);
                } else {
                    colorData.push_back(gray);
                    colorData.push_back(gray);
                    colorData.push_back(gray);

                    colorData.push_back(gray);
                    colorData.push_back(gray);
                    colorData.push_back(gray);

                    colorData.push_back(gray);
                    colorData.push_back(gray);
                    colorData.push_back(gray);
                }
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(float), colorData.data(), GL_STATIC_DRAW);
    }
    wasCPressed = isCPressed;
}