#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <iostream>
#include <string>

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW konnte nicht initialisiert werden!\n";
        return -1;
    }

    

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLAD Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Fenster konnte nicht erstellt werden!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "GLAD konnte OpenGL nicht laden!\n";
        return -1;
    }

    std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    float vertexData[] = 
    {
         -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f         
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 3, vertexData,GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    
    
    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    
    std::string vertexSource = 
    "#version 330 core \n"
    "layout(loation = 0) in vec4  position;"
    "void main()\n"
    "{\n"
    "   gl_Position = position;\n"
    "}\n";
    
    std::string fragmentSource = 
    "#version 330 core\n"
    "layout(location = 0) out vec4 color\n"
    "\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 1.0, 1.0 ,1.0)\n"
    "}\n";
    
    program = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    vertexShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* src1 = vertexSource.c_str();
    const char* src2 = fragmentSource.c_str();
    glShaderSource(vertexShader, 1, &src1, nullptr);
    glShaderSource(vertexShader, 1, &src2, nullptr);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    std::cout << glGetError() << std::endl;         
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)800, (float)800);
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    bool show_demo_window = true;

    while (!glfwWindowShouldClose(window)) {
        


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Begin("Test Window");
        ImGui::Text("Hello");
        ImGui::End();
        
        ImGui::Render();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
