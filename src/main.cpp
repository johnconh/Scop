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
#include <iostream>
#include "../inc/objloader.h"

const GLuint WIDTH = 800, HEIGHT = 600;

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
    std:: string mtlFile;


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

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}