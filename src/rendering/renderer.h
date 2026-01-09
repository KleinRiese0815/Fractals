#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Renderer
{
public:
    enum ShaderTypes{vertex, fragment};
    GLFWwindow* window;
    
    void LoadShader(std::string shaderSource, ShaderTypes type);
    

    void PushBackVertecies();
    void EmptyVertexBuffer();
    void Render();
};
