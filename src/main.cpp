#include "../libs/glew/include/GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../inc/Renderer.h"
#include "../inc/VertexBuffer.h"
#include "../inc/IndexBuffer.h"
#include "../inc/VertexArray.h"
#include "../inc/Shader.h"
#include "../inc/VertexBufferLayout.h"
#include "../inc/Texture.h"
#include "../inc/glm/gtc/matrix_transform.hpp"
#include "../inc/imgui/imgui.h"
#include "../inc/imgui/imgui_impl_glfw.h"
#include "../inc/imgui/imgui_impl_opengl3.h"
#include "../inc/test/TestClearColor.h"
#include "../inc/test/TestTexture2D.h"

int main() {
    
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(960, 540, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    std::cout << "GLEW versión: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL versión: " << glGetString(GL_VERSION) << std::endl;

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }
 
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
    
    while (!glfwWindowShouldClose(window))
    {

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        ImGui_ImplOpenGL3_NewFrame();  
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if(currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Menu Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
    
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}