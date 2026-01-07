#pragma once

#include <string>

unsigned int CompileShader(unsigned int type, const std::string& _source);

unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);