#include<vertex.h>
Vertex::Vertex(float x, float y) :
    x(x), y(y)
{
    
}

Vertex::Vertex() : 
    x(0), y(0)
{

}

Vertex Vertex::operator+(const Vertex& v) const
{
    return Vertex(x + v.x, y + v.y);
}

Vertex Vertex::operator-(const Vertex& v) const
{
    return Vertex(x - v.x, y - v.y);
}

Vertex Vertex::operator*(float f)  const
{
    return Vertex(x * f, y * f);
}

void Vertex::print()
{
    std::cout << "x: " << x <<"   " << "y: " << y << "\n";
}

Vertex Vertex::lerp(const Vertex& v1, const Vertex& v2, float percentage)
{
    return v1 + (v2 - v1) * percentage;
}