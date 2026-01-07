#include <iostream>
#include <filesystem>
#include <fstream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "ShaderHandler.h"
#include "Utility.h"


int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

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

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[12] = {
          -1.f, -0.25f,
        -0.75f,  0.25f,
         -0.5f, -0.25f,

        -0.75f, -0.75f,
          0.0f,  0.75f,
         0.75f, -0.75f
    };

    unsigned int bufferID1, bufferID2;
    glGenBuffers(1, &bufferID1);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID1);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions + 0, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    glGenBuffers(1, &bufferID2);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID2);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions + 6, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string vertexShaderSource = ParseFile("../../../shaders/VertexShader.glsl");
    std::string fragmentShaderSource = ParseFile("../../../shaders/FragmentShader.glsl");
    unsigned int shaderID = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    if (shaderID == -1) {
        return -1;
    }

    glUseProgram(shaderID);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, bufferID1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindBuffer(GL_ARRAY_BUFFER, bufferID2);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderID);

    glfwTerminate();
    return 0;
}

int asd() {
    return 0;
}