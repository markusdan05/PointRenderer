#pragma once

#include <iostream>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader {
private:
    unsigned int m_ShaderProgramID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    int SetUniform1i(const std::string& uniformName, int value) const;
    int SetUniform1f(const std::string& uniformName, float value) const;
    int SetUniformVec4f(const std::string& uniformName, glm::vec4 value) const;
    int SetUniformMat4f(const std::string& uniformName, glm::mat4 value) const;
private:
    static unsigned int CompileShader(unsigned int type, const std::string& _source);
    static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    int GetUniformLocation(const std::string& uniformName) const;
};