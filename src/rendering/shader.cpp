#include <fstream>
#include <shader.h>
#include <iostream>

Shader::Shader(std::string vertexSource, std::string fragmentSource)
{
    id = glCreateProgram();
    
    Bind();
    unsigned int vertexShader = SetupShader(GL_VERTEX_SHADER, vertexSource.c_str());
    unsigned int fragmentShader = SetupShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
    
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glValidateProgram(id);
    
    Unbind();
}

std::string Shader::ReadFromFile(const char* source)
{
    std::ifstream file (source);
    std::string str;
    std::string file_content;
    while(std::getline(file, str))
    {
        file_content += str;
        file_content += '\n';
    }
    return file_content;
}

unsigned int Shader::SetupShader(GLenum shaderType, const char* shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
    std::string shaderSrcString = ReadFromFile(shaderSource);
    const char* shaderSrc = shaderSrcString.c_str();
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);
    
    int compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    
    if(compileStatus == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "EORROR WHILE COMPILING" << (shaderType == GL_VERTEX_SHADER ? "Vertexshader" : "Fragmentshader") << " : "  << message << std::endl;
    }
    return shader;
}

void Shader::Bind()
{
    glUseProgram(id);
}
void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniformMat4f(const char* name, glm::mat4& value)
{
    int location = glGetUniformLocation(id, name);
    if(location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }
}