#include <iostream>
#include <filesystem>
#include <fstream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Utility.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

int main() {
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    const int windowWidth = 640, windowHeight = 480;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    if (!window) {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "glewInit failed!" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenGLDebugCallback, nullptr);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
          -1.f,    1.f, 0.0f, 0.0f,
           0.f,  0.75f, 1.0f, 0.0f,
        -0.75f, -0.75f, 0.0f, 1.0f,
         0.75f, -0.75f, 1.0f, 1.0f
    };

    unsigned int indices[]{
        0, 2, 1,
        1, 2, 3
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(2);
    vertexBufferLayout.Push<float>(2);
    vertexArray.AddVertexBuffer(vertexBuffer, vertexBufferLayout);
    vertexBuffer.UnBind();

    IndexBuffer indexBuffer(indices, 2 * 3);
    indexBuffer.UnBind();

    glm::mat4 projectionMatrix = glm::ortho(-(float)windowWidth / windowHeight, (float)windowWidth / windowHeight, -1.f, 1.f, -1.f, 1.f);
    glm::mat4 modelMatrix = glm::mat4(1.f), viewMatrix = glm::mat4(1.f);

    Shader shader("../../../shaders/VertexShader.glsl", "../../../shaders/FragmentShader.glsl");
    shader.SetUniformVec4f("u_Color", { 0.5f, 0.1f, 0.7f, 1.0f });
    shader.SetUniformMat4f("u_ModelMatrix", modelMatrix);
    shader.SetUniformMat4f("u_ViewMatrix", viewMatrix);
    shader.SetUniformMat4f("u_ProjectionMatrix", projectionMatrix);
    shader.UnBind();

    Texture texture("../../../resources/raisu.jpg");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        renderer.Clear();

        ImGui::ShowDemoWindow(nullptr);
        renderer.Draw(vertexArray, indexBuffer, shader);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}