#include "shader.h"
#include "vertex.h"
#include <iterator>
#include <renderer.h>

Renderer::Renderer(int windowWidth, int windowHeight, GLFWwindow* window, Shader shader):
    m_vertecies(0), m_projection(glm::mat4(1.0))
{
    //Set projection matrix
    m_projection = glm::ortho(-windowWidth / 2.0f, windowWidth / 2.0f, -windowHeight / 2.0f, windowHeight / 2.0f, -1.0f, 1.0f);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); 
   
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
    
    shader.Bind();

    shader.SetUniformMat4f("projection", m_projection);
}

void Renderer::PushBackVertecies(Vertex* vertecies, int count)
{
    size_t oldSize = m_vertecies.size();
    size_t newSize = oldSize + count;
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    if(newSize > m_vertecies.capacity())
    {
        m_vertecies.reserve(newSize * 2);
        glBufferData(GL_ARRAY_BUFFER, m_vertecies.capacity() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, oldSize * sizeof(Vertex), m_vertecies.data());
    }

    m_vertecies.insert(m_vertecies.end(), vertecies, vertecies + count);
    
    glBufferSubData(GL_ARRAY_BUFFER, oldSize * sizeof(Vertex), count * sizeof(Vertex), vertecies);
}

void Renderer::PushBackIndecies(unsigned int* indecies, int count)
{
    glBindVertexArray(m_vao);
    size_t oldSize = m_indecies.size();
    size_t newSize = oldSize + count;


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    
    if(newSize > m_indecies.capacity())
    {
        m_indecies.reserve(newSize * 2);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indecies.capacity() * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, oldSize * sizeof(unsigned int), m_indecies.data());
    }

    m_indecies.insert(m_indecies.end(), indecies, indecies + count);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, oldSize * sizeof(unsigned int), count * sizeof(unsigned int), indecies);
}

void Renderer::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glDrawElements(GL_TRIANGLES, m_indecies.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::PushBackTriangle(Vertex point1, Vertex point2, Vertex point3)
{
    unsigned int offset = m_vertecies.size();
    Vertex vertecies[] = 
    {
        Vertex(point1.x, point1.y),
        Vertex(point2.x, point2.y),
        Vertex(point3.x, point3.y)
    };


    unsigned int indecies[] = 
    {
        offset + 0, offset + 1, offset + 2
    };
    

    PushBackVertecies(vertecies, 3);
    PushBackIndecies(indecies, 3);
    std::cout << "-------------------------------_"<<std::endl;
    std::cout << "Vertecies:" << std::endl;
    for(int i = 0; i < m_vertecies.size(); i++)
    {
        std::cout << m_vertecies[i].x << "," << m_vertecies[i].y << std::endl;
    }
    std::cout << "Indecies:" << std::endl;
    for(int i = 0; i < m_indecies.size(); i++)
    {
        std::cout << m_indecies[i] <<std::endl;
    } 
}

void Renderer::PushBackSquare(glm::vec2 lowerLeft, glm::vec2 lowerRight, glm::vec2 upperLeft, glm::vec2 upperRight)
{
    unsigned int offset = m_vertecies.size();
    Vertex vertecies[] = 
    {
        Vertex(lowerLeft.x, lowerLeft.y),
        Vertex(lowerRight.x, lowerRight.y),
        Vertex(upperLeft.x, upperLeft.y),
        Vertex(upperRight.x, upperRight.y)
    };

    
    unsigned int indecies[] = 
    {
        offset, offset + 1, offset + 3,
        offset + 3, offset + 2, offset + 0
    };

    PushBackVertecies(vertecies, 4);
    PushBackIndecies(indecies, 6);
}

std::vector<Vertex>& Renderer::GetVertexRef() { return m_vertecies;}
std::vector<unsigned int>& Renderer::GetIndexRef() { return m_indecies; }

void Renderer::Empty()
{
    m_vertecies = std::vector<Vertex>();
    m_indecies = std::vector<unsigned int>();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
}