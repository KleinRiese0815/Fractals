#pragma once
#include <iostream>

struct Vertex
{
public:
    float x, y;
    Vertex(float, float);
    Vertex();

    Vertex operator+(const Vertex& v) const;
    Vertex operator-(const Vertex& v) const;
    Vertex operator*(float v) const;
    
    static Vertex lerp(const Vertex& v1, const Vertex& v2, const float percentage);    
    
    void print();
};
