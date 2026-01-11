#include "Shader.h"

#include <unordered_map>

#include "Utility.h"

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
    std::string vertexShaderSource = ParseFile(vertexFilePath);
    std::string fragmentShaderSource = ParseFile(fragmentFilePath);
    m_ShaderProgramID = Shader::CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    if (m_ShaderProgramID == -1) {
        __debugbreak();
    }
}

Shader::~Shader() {
    glDeleteProgram(m_ShaderProgramID);
}

void Shader::Bind() const {
    glUseProgram(m_ShaderProgramID);
}

void Shader::UnBind() const {
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& uniformName) const {
    if (auto searchResult = m_UniformLocationCache.find(uniformName); searchResult != m_UniformLocationCache.end()) {
        return searchResult->second;
    }
    else {
        int location = glGetUniformLocation(m_ShaderProgramID, uniformName.c_str());
        m_UniformLocationCache[uniformName] = location;
        return location;
    }
}

int Shader::SetUniform1i(const std::string& uniformName, int value) const {
    Bind();
    int location = GetUniformLocation(uniformName);
    if (location == -1) {
        std::cout << "Uniform <" << uniformName << "> not found!" << std::endl;
        return -1;
    }
    glUniform1i(location, value);
    return 0;
}

int Shader::SetUniform1f(const std::string& uniformName, float value) const {
    Bind();
    int location = GetUniformLocation(uniformName);
    if (location == -1) {
        std::cout << "Uniform <" << uniformName << "> not found!" << std::endl;
        return -1;
    }
    glUniform1f(location, value);
    return 0;
}

int Shader::SetUniformVec4f(const std::string& uniformName, glm::vec4 value) const {
    Bind();
    int location = GetUniformLocation(uniformName);
    if (location == -1) {
        std::cout << "Uniform <" << uniformName << "> not found!" << std::endl;
        return -1;
    }
    glUniform4f(location, value.x, value.y, value.z, value.w);
    return 0;
}

int Shader::SetUniformMat4f(const std::string& uniformName, glm::mat4 value) const {
    Bind();
    int location = GetUniformLocation(uniformName);
    if (location == -1) {
        std::cout << "Uniform <" << uniformName << "> not found!" << std::endl;
        return -1;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    return 0;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& _source) {
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

unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int programID = glCreateProgram();

    unsigned int vertexShaderID = Shader::CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShaderID = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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
