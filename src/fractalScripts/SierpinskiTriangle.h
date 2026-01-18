#pragma once

#include "vertex.h"
#include<renderer.h>
#include<vector>
#include<fractal.h>

class SierpinskiTrinagle : public Fractal
{
    Renderer* renderer; 
    int currentDepth;       //How many times the Fractal ist iteratet

    const int lowerLeftVertexOffset = 0;
    const int lowerRightVertexOffset = 1;
    const int middleCornerOffset = 2;
    
public:
    SierpinskiTrinagle(Renderer* renderer);

    std::vector<Vertex> Recursion(int depth, std::vector<Vertex>& vertecies);

    void SetRecursionDepth(int desiredDepth) override;
};
