#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
private:
    unsigned int id;
    unsigned int SetupShader(GLenum shaderType, const char* source);
public:
    std::string fragmentSource;
    std::string vertexSource;
    
    Shader(std::string, std::string);
    void Bind();
    void Unbind();
    
    void SetUniformMat4f(const char* name, glm::mat4& value);

private:
    std::string ReadFromFile(const char* source);
};