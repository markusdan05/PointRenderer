#pragma once

#include <iostream>
#include <unordered_map>

class Shader {
private:
    unsigned int m_ShaderProgramID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    int SetUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3);
private:
    static unsigned int CompileShader(unsigned int type, const std::string& _source);
    static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    int GetUniformLocation(const std::string& uniformName) const;
};