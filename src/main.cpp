#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <shader.h>
#include <filesystem>
#include <renderer.h>
#include <fractal.h>
#include <gui.h>
#include <SierpinskiTriangle.h>
#include <KochSnowflake.h>
#include <computeShader.h>

GeometryFractalTypes currentType = kochSnowflake;

void OnFileOpen(GeometryFractalTypes);

void(*onGeometrySelectMethode)(GeometryFractalTypes) = OnFileOpen;


int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW konnte nicht initialisiert werden!\n";
        return -1;
    }
    
    const int resolutionX = 1920, resolutionY = 1080;
    
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow* window = glfwCreateWindow(resolutionX, resolutionY, "GLAD Test", nullptr, nullptr);
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
    
    Shader shader(std::filesystem::current_path().parent_path() / "shader/shader.vert", std::filesystem::current_path().parent_path() / "shader/shader.frag"); 
    shader.Bind();
    
    Renderer renderer(screen_width, screen_height, window, shader);
    
    Gui::Init(screen_width, screen_height, window);
    
    Gui::SetGeometryCallBack(onGeometrySelectMethode);
    
    KochSnowflake snowFlake(&renderer);
    snowFlake.SetRecursionDepth(5);
    
    SierpinskiTrinagle sierpinskiTriangle(&renderer);
    sierpinskiTriangle.SetRecursionDepth(5);
    
    ComputeShader computeShader("shader/shader.comp");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Gui::UpdateVisuals();
       
        if(currentType == kochSnowflake)
        {
            snowFlake.OnDraw();
        }else if(currentType == GeometryFractalTypes::sierpinskiTriangle)
        {
            sierpinskiTriangle.OnDraw();
        }

        Gui::Render();
        
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

void OnFileOpen(GeometryFractalTypes type)
{
    currentType = type;    
}
