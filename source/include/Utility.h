#pragma once

#include <iostream>

#include "GL/glew.h"

std::string ParseFile(const std::string& filePath);

void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);