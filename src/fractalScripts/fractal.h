#pragma once

enum MathFractalTypes
{
    Mandelbrotset
};

enum GeometryFractalTypes
{
    sierpinskiTriangle, kochSnowflake
};

class Fractal 
{
public:
    virtual ~Fractal() = default;
    virtual void SetRecursionDepth(int desiredDepth) = 0;
    virtual void OnDraw() = 0;
};
