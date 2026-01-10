#pragma once
#include <glad/glad.h>
#include <string>

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

private:
    std::string ReadFromFile(const char* source);
};