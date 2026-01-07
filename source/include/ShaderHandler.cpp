#include <iostream>

#include "GL/glew.h"
#include "ShaderHandler.h"

unsigned int CompileShader(unsigned int type, const std::string& _source) {
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

unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
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