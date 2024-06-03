#include "../libs/glew/include/GL/glew.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

// Error callback para GLFW
void error_callback(int /*error*/, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Key callback para manejar eventos del teclado
void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Función para configurar la matriz de proyección
void set_perspective(float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov * 0.5f * (M_PI / 180.0f));
    float proj[16] = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (far + near) / (near - far), -1.0f,
        0.0f, 0.0f, (2.0f * far * near) / (near - far), 0.0f
    };
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(proj);
}

int main(void) {
    // Inicializar GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Configurar el error callback
    glfwSetErrorCallback(error_callback);

    // Crear una ventana
    GLFWwindow* window = glfwCreateWindow(640, 480, "Scop without GLEW", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Inicializar GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    // Verificar si GLEW está disponible
    std::cout << "GLEW versión: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL versión: " << glGetString(GL_VERSION) << std::endl;

    // Hacer el contexto OpenGL actual
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Configurar el viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Configurar la proyección
    set_perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Limpiar la pantalla
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configurar la vista y la transformación del modelo
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);

        // Rotar el triángulo
        static float angle = 0.0f;
        angle += 0.1f;
        glRotatef(angle, 0.0f, 1.0f, 0.0f);

        // Dibujar un triángulo
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glEnd();

        // Intercambiar buffers
        glfwSwapBuffers(window);
        // Procesar eventos
        glfwPollEvents();
    }

    // Limpiar y cerrar
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
