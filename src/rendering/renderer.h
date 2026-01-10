#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <shader.h>

class Renderer
{
private:
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ibo;
public:

    enum ShaderTypes{vertex, fragment};
    GLFWwindow* window;

    Renderer(GLFWwindow* window, Shader shader);
    void LoadShader(std::string shaderSource, ShaderTypes type);

    void PushBackVertecies();
    void EmptyVertexBuffer();
    void Render();
};
