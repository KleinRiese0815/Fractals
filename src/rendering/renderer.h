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
class Renderer
{
private:
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ibo;

    std::vector<Vertex> m_vertecies;
    std::vector<unsigned int> m_indecies;

    glm::mat4 m_projection;
public:

    enum ShaderTypes{vertex, fragment};
    GLFWwindow* window;

    Renderer(int, int, GLFWwindow* window, Shader shader);
    void LoadShader(std::string shaderSource, ShaderTypes type);

    void PushBackVertecies(Vertex* vertecies, int count);
    void PushBackIndecies(unsigned int*, int);
    void EmptyVertexBuffer();
    void Render();
    
    void PushBackTriangle(Vertex point1, Vertex point2, Vertex point3);
    void PushBackSquare(glm::vec2 lowerLeft, glm::vec2 lowerRight, glm::vec2 upperLeft, glm::vec2 upperRight);

    std::vector<Vertex>& GetVertexRef();
    std::vector<unsigned int>& GetIndexRef();

    void Empty();
};
