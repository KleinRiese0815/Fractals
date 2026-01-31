#include "VboIndex.h"
#include "shader.h"
#include "vertex.h"
#include <iterator>
#include <renderer.h>
#include <vector>

Renderer::Renderer(int windowWidth, int windowHeight, GLFWwindow* window, Shader shader):
    m_vertexBufferContents(0), m_projection(glm::mat4(1.0)), m_currentMode(RenderMode::DrawElements)
{
    //Set projection matrix
    m_projection = glm::ortho(-windowWidth / 2.0f, windowWidth / 2.0f, -windowHeight / 2.0f, windowHeight / 2.0f, -1.0f, 1.0f);

    glGenVertexArrays(1, &m_vao);
    
    shader.Bind();

    shader.SetUniformMat4f("projection", m_projection);
}

void Renderer::PushBackVertecies(Vertex* vertecies, int count, VboIndex vboIndex = {0})
{
    std::vector<Vertex>& selectedVertexBuffer = m_vertexBufferContents[static_cast<size_t>(vboIndex)];

    size_t oldSize = selectedVertexBuffer.size();
    size_t newSize = oldSize + count;
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[static_cast<size_t>(vboIndex)]);
    
    if(newSize > selectedVertexBuffer.capacity())
    {
        selectedVertexBuffer.reserve(newSize * 2);
        glBufferData(GL_ARRAY_BUFFER, selectedVertexBuffer.capacity() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, oldSize * sizeof(Vertex), selectedVertexBuffer.data());
    }

    selectedVertexBuffer.insert(selectedVertexBuffer.end(), vertecies, vertecies + count);
    
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

void Renderer::Render(int ibo = 0, VboIndex vbo = { 0 })
{
    BindVboToVao(vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    
    if(m_currentMode == DrawElements)
    {
        glDrawElements(GL_TRIANGLES, m_indecies.size(), GL_UNSIGNED_INT, nullptr);
    }else if(m_currentMode == DrawArrays)
    {
        glDrawArrays(GL_TRIANGLES, 0, m_vertexBufferContents[static_cast<size_t>(vbo)].size());
    }
    else if(m_currentMode == DrawLines) 
    {
        glDrawArrays(GL_LINES, 0, m_vertexBufferContents[static_cast<size_t>(vbo)].size());
    }
}

std::vector<Vertex>& Renderer::GetVertexBufferContents(VboIndex index) {  return m_vertexBufferContents[static_cast<size_t>(index)];  }
std::vector<unsigned int>& Renderer::GetIndexRef() { return m_indecies; }


//Do not use
void Renderer::Empty()
{
    std::cout << "Function is work in progress, should not be used!!!" << std::endl;

    m_vertexBufferContents = std::vector<std::vector<Vertex>>();
    m_indecies = std::vector<unsigned int>();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
}

VboIndex Renderer::CreateVertexBuffer()
{
    unsigned int vbo = 0;
    glBindVertexArray(m_vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);

    m_vbos.push_back(vbo);
    m_vertexBufferContents.push_back(std::vector<Vertex>());

    return VboIndex{m_vbos.size() - 1 };
}

void Renderer::SetRenderMode(RenderMode desiredMode) {  m_currentMode = desiredMode; }

void Renderer::BindVboToVao(VboIndex vbo)
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[static_cast<size_t>(vbo)]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
}