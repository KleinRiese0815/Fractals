#pragma once
class Fractal 
{
public:
    virtual ~Fractal() = default;
    virtual void SetRecursionDepth(int desiredDepth) = 0;
};
