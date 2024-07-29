/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 14:28:28 by jdasilva          #+#    #+#             */
/*   Updated: 2024-07-10 14:28:28 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Matrix.h"
#include "objloader.h"

void handleInput(GLFWwindow *window, Matrix4& model, Vector3& objectmovement, float movementSpeed, float deltaTime, bool &useTexture);
void handleColor(GLFWwindow *window, GLuint colorBuffer, const std::vector<Face>& faces, std::vector<float> colorData, bool &useColor);
#endif