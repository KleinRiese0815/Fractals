#include <renderer.h>

Renderer::Renderer(GLFWwindow* window, Shader shader)
{
    float vertexData[] = 
    {
         -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f         
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); 
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), &vertexData, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
    
    shader.Bind();
}
