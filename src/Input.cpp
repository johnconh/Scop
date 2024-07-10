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

void handleInput(GLFWwindow *window, Matrix4& model, Vector3& objectMovement, float movementSpeed, float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        objectMovement.z -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, 0.0f, -movementSpeed);
        model = operator*(model, translation);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        objectMovement.z += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, 0.0f, movementSpeed);
        model = operator*(model, translation);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        objectMovement.x -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(-movementSpeed, 0.0f, 0.0f);
        model = operator*(model, translation);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        objectMovement.x += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(movementSpeed, 0.0f, 0.0f);
        model = operator*(model, translation);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        objectMovement.y += movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, movementSpeed, 0.0f);
        model = operator*(model, translation);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        objectMovement.y -= movementSpeed * deltaTime;
        Matrix4 translation = translateMatrix(0.0f, -movementSpeed, 0.0f);
        model = operator*(model, translation);
    }
}
