#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <shader.h>
#include <vertex.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <VboIndex.h>

enum RenderMode
{
    DrawArrays, DrawElements, DrawLines  
};


class Renderer
{
private:
    unsigned int m_vao;
    unsigned int m_ibo;
    
    RenderMode m_currentMode;

    std::vector<unsigned int> m_vbos;

    std::vector<std::vector<Vertex>> m_vertexBufferContents;
    std::vector<unsigned int> m_indecies;

    glm::mat4 m_projection;

    void BindVboToVao(VboIndex vbo);
public:

    enum ShaderTypes{vertex, fragment};
    GLFWwindow* window;

    Renderer(int, int, GLFWwindow* window, Shader shader);
    void LoadShader(std::string shaderSource, ShaderTypes type);

    void PushBackVertecies(Vertex* vertecies, int count, VboIndex vboIndex);
    void PushBackIndecies(unsigned int* indecies, int count);
    void EmptyVertexBuffer();
    void Render(int ibo, VboIndex vbo);
    
    std::vector<Vertex>& GetVertexBufferContents(VboIndex index);
    std::vector<unsigned int>& GetIndexRef();

    void Empty();

    VboIndex CreateVertexBuffer();

    void SetRenderMode(RenderMode);
};