#include "fractal.h"
#include "imgui.h"
#include<gui.h>

int Gui::displayHeight = 0;
int Gui::displayWidth = 0;

void(*Gui::geometryFractalSelectCallback)(GeometryFractalTypes) = nullptr;
void(*Gui::mathFractalSelectCallback)(MathFractalTypes) = nullptr;


void Gui::Init(int displayWidth, int displayHeight, GLFWwindow* window)
{
    Gui::displayHeight = displayHeight;
    Gui::displayWidth = displayWidth;
    std::cout << "Resolution: " << displayWidth << " , " << displayHeight << std::endl;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)displayWidth, (float)displayHeight);
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void Gui::Render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::UpdateVisuals()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    
    ImGui::NewFrame();
    MenuBar::Render();
    PropertyWindow::Render();
    ImGui::Render();
}

void MenuBar::Render()
{   
    if(ImGui::BeginMainMenuBar())
    {  
        
        //File Menu
        if(ImGui::BeginMenu("File"))
        {
            
            if(ImGui::BeginMenu("Open"))
            {
                if(ImGui::MenuItem("Sierpinski Triangle") && Gui::geometryFractalSelectCallback)
                {
                    Gui::geometryFractalSelectCallback(GeometryFractalTypes::sierpinskiTriangle);
                }

                if(ImGui::MenuItem("Kochsche Schneeflocke") && Gui::geometryFractalSelectCallback)
                {
                    Gui::geometryFractalSelectCallback(GeometryFractalTypes::kochSnowflake);
                }
                
                ImGui::EndMenu();
            }

            ImGui::MenuItem("New");

            ImGui::MenuItem("Save");

            ImGui::MenuItem("Quit");

            ImGui::EndMenu();
        }

        //Help Menu
        ImGui::MenuItem("Help");


        ImGui::EndMainMenuBar();    
    }
}

void PropertyWindow::Render()
{
    ImGuiWindowFlags windowflags = 0;
    
    windowflags |= ImGuiWindowFlags_NoScrollbar;
    windowflags |= ImGuiWindowFlags_NoMove;
    windowflags |= ImGuiWindowFlags_NoResize;
    windowflags |= ImGuiWindowFlags_NoCollapse;
    windowflags |= ImGuiWindowFlags_NoNav;
    
    const int windowWidth = 700 ;

    ImGui::SetNextWindowPos(ImVec2(Gui::displayWidth - (windowWidth / 2), 0));
    ImGui::SetNextWindowSize(ImVec2(windowWidth, Gui::displayHeight));

    ImGui::Begin("Properties", NULL, windowflags);
    ImGui::End();
}

void Gui::SetGeometryCallBack(void (*callback)(GeometryFractalTypes))
{
    Gui::geometryFractalSelectCallback = callback;
}

void Gui::SetMathCallback(void (*callback)(MathFractalTypes))
{
    Gui::mathFractalSelectCallback = callback;
}