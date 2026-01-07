#include <iostream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "Utility.h"

static unsigned int CompileShader(unsigned int type, const std::string& _source) {
    unsigned int shaderID = glCreateShader(type);

    const char* source = _source.c_str();
    const int length = _source.length();
    glShaderSource(shaderID, 1, &source, &length);
    glCompileShader(shaderID);

    int shaderCompilationStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompilationStatus);
    if(shaderCompilationStatus == GL_FALSE) {
        int infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::unique_ptr<char> message = std::make_unique<char>(infoLogLength * sizeof(char));
        glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, message.get());
        std::cout << (
            type == GL_VERTEX_SHADER ? "Vertex" :
            type == GL_FRAGMENT_SHADER ? "Fragment" :
            "Unknown type"
            ) << " shader compilation error!\n";
        std::cout << message << std::endl;

        glDeleteShader(shaderID);
        return -1;
    }

    return shaderID;
}

static unsigned int CreateShaders(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int programID = glCreateProgram();

    unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vertexShaderID == -1 || fragmentShaderID == -1) {
        std::cout << "Shader compilation error!" << std::endl;
        return -1;
    }

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);
    glValidateProgram(programID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

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

    std::string vertexShaderSource =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    std::string fragmentShaderSource =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(0.5, 0.0, 0.7, 1.0);\n"
        "}\n";
    unsigned int shaderID = CreateShaders(vertexShaderSource, fragmentShaderSource);
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