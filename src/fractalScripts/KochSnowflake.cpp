#include "KochSnowflake.h"

/*
Construction of the Koch kurve
The Koch snowflake can be constructed by starting with an equilateral triangle, then recursively altering each line segment as follows:

    1. divide the line segment into three segments of equal length.
    2. draw an equilateral triangle that has the middle segment from step 1 as its base and points outward.
    3.remove the line segment that is the base of the triangle from step 2.

The first iteration of this process produces the outline of a hexagram.

The Koch snowflake is the limit approached as the above steps are followed indefinitely. The Koch curve originally described by Helge von Koch is constructed using only one of the three sides of the original triangle. In other words, three Koch curves make a Koch snowflake.

A Koch curve–based representation of a nominally flat surface can similarly be created by repeatedly segmenting each line in a sawtooth pattern of segments with a given angle.          

|------------------------------------------------------|
|                        IMAGE                         |
|------------------------------------------------------|
|                                                      |
|                          |---->C                     |
|                          x                           |
|                         ---                          |
|                        -----                         |
|              x-------x-------x-------x               |
|              |       |       |       |               |
|              V       V       V       V               |
|              A       B       D       E               |
|------------------------------------------------------|

source : https://en.wikipedia.org/wiki/Koch_snowflake
*/




KochSnowflake::KochSnowflake(Renderer* renderer) :
    renderer(renderer)
{
    m_vboIndex = renderer->CreateVertexBuffer();
    m_vertecies = std::vector<Vertex>();
}

std::vector<Vector> KochSnowflake::Recursion(int depth, std::vector<Vector> last)
{
    std::vector<Vector> current;
    if(depth == 0)
    {
        return last;
    }else {
        for(int i = 0; i < last.size(); i ++)
        {
            Vertex A = last[i].p1; //start Point from the  old line
            Vertex E = last[i].p2; //end Point from the old line
 
            Vertex B = Vertex::lerp(A, E, (float)1/3);
            Vertex D = Vertex::lerp(A, E, (float)2/3);
            
            //Calculation of C:
            const Vector orthagonal = Vector::GetOrthagonal(last[i]); //Vector wich is orthagonal to a line, crossing Point A and E
            Vertex middlePoint = A + ((E - last[i].p1) * 0.5); //Vector Point in the middle between pont A and E, used to construct C
            Vertex C = middlePoint + Vertex(orthagonal.x, orthagonal.y) * 0.25f; //construction of C
            
            //pushing back the calculatet Vertecies to form replace old (straight) line with the new ones (look at image above Image) 
            current.push_back(Vector(A, B));
            current.push_back(Vector(B, C));
            current.push_back(Vector(C, D));
            current.push_back(Vector(D, E));
        }
        return Recursion(depth - 1, current);
    }
}

void KochSnowflake::SetRecursionDepth(int desiredDepth)
{
    m_vertecies.clear();

    std::vector<Vector> starter;
    starter.push_back(Vector(Vertex(200, -200), Vertex(-200, -200)));
    starter.push_back(Vector(Vertex(-200, -200), Vertex(0, 200)));
    starter.push_back(Vector(Vertex(0, 200), Vertex(200, -200)));
    std::vector<Vector> result = Recursion(desiredDepth, starter);

    for(int i = 0; i < result.size();i ++)
    {
        m_vertecies.push_back(result[i].p1);
        m_vertecies.push_back(result[i].p2);
    }

    renderer->PushBackVertecies(m_vertecies.data(), m_vertecies.size(), m_vboIndex);
}
void KochSnowflake::OnDraw()
{
    renderer->SetRenderMode(RenderMode::DrawLines);
    renderer->Render(0, m_vboIndex);
}

KochSnowflake::~KochSnowflake() = default;