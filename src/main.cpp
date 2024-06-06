#include "../libs/glew/include/GL/glew.h"
#include <GLFW/glfw3.h>
#include "../inc/Renderer.h"
#include "../inc/VertexBuffer.h"
#include "../inc/IndexBuffer.h"
#include "../inc/VertexArray.h"
#include "../inc/Shader.h"

int main() {
    
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear una ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    // Hacer que la ventana sea el contexto actual
    glfwMakeContextCurrent(window);
    
    //glfwSwapInterval(1); // Habilitar VSync

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

    float position[] = {
        -0.5f, -0.5f, // 0
        0.5f, -0.5f, // 1
        0.5f, 0.5f, // 2
        -0.5f, 0.5f // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexArray va;
    VertexBuffer vb(position, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    
    IndexBuffer ibo(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    
    va.Unbind();
    vb.Unbind();
    ibo.Unbind();
    shader.Unbind();

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        va.Bind();
        ibo.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    // Cerrar GLFW y terminar
    glfwTerminate();
    return 0;
}