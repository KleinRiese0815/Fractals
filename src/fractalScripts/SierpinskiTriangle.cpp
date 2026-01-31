#include <SierpinskiTriangle.h>

SierpinskiTrinagle::SierpinskiTrinagle(Renderer* renderer) :
    renderer(renderer), m_vboIndex(renderer->CreateVertexBuffer())
{
    
}

std::vector<Vertex> SierpinskiTrinagle::Recursion(int depth, std::vector<Vertex>& vertecies)
{
    std::vector<Vertex> nextVertecies;
    for(int i = 0; i < vertecies.size(); i += 3)
    {
        Vertex lowerLeft = vertecies[i + lowerLeftVertexOffset];
        Vertex lowerRight = vertecies[i + lowerRightVertexOffset];
        Vertex middle = vertecies[i + middleCornerOffset];

        //left triangle
        nextVertecies.push_back(lowerLeft);
        nextVertecies.push_back(Vertex((lowerRight.x + lowerLeft.x) / 2, lowerLeft.y));
        nextVertecies.push_back(Vertex((middle.x + lowerLeft.x) / 2, (middle.y + lowerLeft.y) / 2));

        //right triangle
        nextVertecies.push_back(Vertex((lowerRight.x + lowerLeft.x) / 2, lowerLeft.y)); //left
        nextVertecies.push_back(lowerRight);  //right
        nextVertecies.push_back(Vertex((middle.x + lowerRight.x) / 2, (middle.y + lowerRight.y) / 2));  //middle

        //middle trinagle
        nextVertecies.push_back(Vertex((middle.x + lowerLeft.x) / 2, (middle.y + lowerLeft.y) / 2)); //left
        nextVertecies.push_back(Vertex((middle.x + lowerRight.x) / 2, (middle.y + lowerRight.y) / 2)); //right
        nextVertecies.push_back(middle); //middle
    }
    if(depth > 1)
    {
        return(Recursion(depth - 1, nextVertecies));
    }else {
    return nextVertecies; //end
    }           
}

void SierpinskiTrinagle::SetRecursionDepth(int desiredDepth)
{
    
    std::vector<Vertex> start;
    start.push_back(Vertex(-400, -400));  //left
    start.push_back(Vertex(400, -400)); //right
    start.push_back(Vertex(0, 400)); //middle
    
    std::vector<Vertex> vertecies = Recursion(desiredDepth, start);
    renderer->PushBackVertecies(vertecies.data(), vertecies.size(), m_vboIndex);
    renderer->SetRenderMode(DrawArrays);

    currentDepth = desiredDepth;
}

void SierpinskiTrinagle::OnDraw()
{
    renderer->SetRenderMode(RenderMode::DrawArrays);
    renderer->Render(0, m_vboIndex);
}