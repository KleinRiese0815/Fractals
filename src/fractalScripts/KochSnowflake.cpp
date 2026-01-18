#include "KochSnowflake.h"
#include "vertex.h"
#include <vector>

KochSnowflake::KochSnowflake(Renderer* renderer) :
    renderer(renderer)
{

}

std::vector<Vertex> KochSnowflake::Recursion(int depth, std::vector<Vertex> vertecies)
{
    int oldSize =    
    std::vector<Vertex> newVertecies;

    for(int i = 0; i < vertecies.size(); i += 3)
    {

    }
}

void KochSnowflake::SetRecursionDepth(int desiredDepth)
{

}