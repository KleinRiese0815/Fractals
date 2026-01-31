#pragma once
#include <cstdlib>
#include "vertex.h"
#include <renderer.h>
#include <vector>
#include <fractal.h>

struct Vector
{
    Vertex p1;
    Vertex p2;

    float x;
    float y;
    Vector(Vertex p1, Vertex p2) :
        p1(p1), p2(p2), 
        x(p1.x - p2.x), y(p1.y - p2.y)
    {
    }

    Vector (float x, float y) :
        x(x), y(y),
        p1(0, 0), p2(x, y)
    {

    }

    Vector() = delete;

    static Vector GetOrthagonal(Vector vec1)
    {
        return Vector(vec1.y, -vec1.x);
    }

    float GetMagnitude()
    {
        const int res =std::sqrt(x*x + y*y);
        return res;
    }
};


class KochSnowflake : public Fractal
{
private:
    Renderer* renderer; 
    int m_currentDepth;

    const int LeftVertexOffset = 0;
    const int RightVertexOffset = 1;
    const int MiddleVertexOffset = 2;

    VboIndex m_vboIndex;

    std::vector<Vertex> m_vertecies;
public:
    KochSnowflake(Renderer* renderer);

    std::vector<Vector> Recursion(int depth, std::vector<Vector> last);
    void SetRecursionDepth(int desiredDepth) override;

    void OnDraw() override;
    virtual ~KochSnowflake() override;
};
