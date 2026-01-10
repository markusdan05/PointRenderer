#include <iostream>
#include <filesystem>
#include <fstream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLEW_STATIC
#include "GL/glew.h"

#include "Utility.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
          -1.f,    1.f,
           0.f,  0.75f,
        -0.75f, -0.75f,
         0.75f, -0.75f
    };

    unsigned int indices[]{
        0, 2, 1,
        1, 2, 3
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout vbl;
    vbl.Push<float>(2);
    va.AddVertexBuffer(vb, vbl);
    vb.UnBind();

    IndexBuffer ib(indices, 2 * 3);
    ib.UnBind();

    Shader shader("../../../shaders/VertexShader.glsl", "../../../shaders/FragmentShader.glsl");
    shader.SetUniform4f("u_Color", 0.5f, 0.1f, 0.7f, 1.0f);
    shader.UnBind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.5f, 0.1f, 0.7f, 1.0f);

        va.Bind();
        ib.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}