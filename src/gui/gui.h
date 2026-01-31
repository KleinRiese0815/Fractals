#pragma once
#include "imgui_impl_glfw.h"
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <imgui.h>
#include <fractal.h>
void guiInit(int displayWidth, int displayHeight, GLFWwindow* window);


class  Gui
{
public:
    static int displayWidth;
    static int displayHeight;
    static void(*geometryFractalSelectCallback)(GeometryFractalTypes);
    static void(*mathFractalSelectCallback)(MathFractalTypes);
    
public:
    static void Init(int, int, GLFWwindow*);
    static void Render();
    static void UpdateVisuals();
    static void SetGeometryCallBack(void(*)(GeometryFractalTypes));
    static void SetMathCallback(void(*)(MathFractalTypes));
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


