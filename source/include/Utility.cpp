#include "Utility.h"

#include <iostream>
#include <fstream>

#include "GL/glew.h"

std::string ParseFile(const std::string& filePath) {
    std::fstream fileStream(filePath, std::ios_base::in);
    if (!fileStream.is_open()) {
        std::cout << "Failed to open shader file <" << filePath << ">!" << std::endl;
        return "";
    }

    fileStream.seekg(0, std::ios::end);
    int fileLength = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);

    std::string parsedFile(fileLength, '\0');
    fileStream.read(&parsedFile[0], fileLength);

    return parsedFile;
}

void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data) {

    // if (severity != GL_DEBUG_SEVERITY_HIGH) return;
    // if (severity != GL_DEBUG_SEVERITY_HIGH && severity != GL_DEBUG_SEVERITY_MEDIUM) return;
    if (severity != GL_DEBUG_SEVERITY_HIGH && severity != GL_DEBUG_SEVERITY_MEDIUM && severity != GL_DEBUG_SEVERITY_LOW) return;

    char* _source;
    char* _type;
    char* _severity;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }

    // printf("%d: %s of %s severity, raised from %s: %s\n", id, _type, _severity, _source, msg);

    std::cout << "OpenGL Error " << id << "!"
        "\nType: " << _type <<
        "\nSeverity: " << _severity <<
        "\nSource: " << _source <<
        "\nMessage: " << msg << std::endl;

    __debugbreak();
}