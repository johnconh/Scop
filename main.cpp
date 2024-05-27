#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    // Crear una ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    // Hacer que el contexto de la ventana sea actual
    glfwMakeContextCurrent(window);
    // Verificar si GLEW está disponible
    // Verificar si GLEW está disponible
    std::cout << "GLEW versión: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL versión: " << glGetString(GL_VERSION) << std::endl;

    // Inicializar GLEW después de haber creado el contexto OpenGL
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    // Cerrar GLFW y terminar
    glfwTerminate();
    return 0;
}