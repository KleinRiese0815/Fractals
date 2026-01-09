#include "imgui_impl_glfw.h"
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

void guiInit(int displayWidth, int displayHeight, GLFWwindow* window);

class  Gui
{
public:
    static int displayWidth;
    static int displayHeight;
    
    
public:
    static void Init(int, int, GLFWwindow*);
    static void Render();
    static void UpdateVisuals();
};

class MenuBar
{
    public:
        void static Render();
};

class PropertyWindow
{
    public:
        void static Render();
};


