#include "vertex.h"
#include <fractal.h>
#include <renderer.h>
#include <vector>

class KochSnowflake : public Fractal
{
    Renderer* renderer; 

    const int lowerLeftVertexOffset = 0;
    const int lowerRightVertexOffset = 1;
    const int middleCornerOffset = 2;
public:
    void SetRecursionDepth(int desiredDepth) override;

    std::vector<Vertex> Recursion(int depth, std::vector<Vertex>);
    KochSnowflake(Renderer* renderer);
};
