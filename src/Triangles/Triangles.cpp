#include "Triangle/Triangles.h"

Triangles::Triangles()
    : v0(0.0f),
      v1(0.0f),
      v2(0.0f),
      vertices{v0, v1, v2}
{
}

Triangles::Triangles(const Vector4f& v0_,
                     const Vector4f& v1_,
                     const Vector4f& v2_)
    : v0(v0_),
      v1(v1_),
      v2(v2_),
      vertices{v0_, v1_, v2_}
{
}

Triangles::Triangles(const Vector3f& vert0_, const Vector3f& vert1_, const Vector3f& vert2_) : vert0(vert0_), vert1(vert1_), vert2(vert2_) {}


Vector4f Triangles::getV0() const
{
    return v0;
}

Vector4f Triangles::getV1() const
{
    return v1;
}

Vector4f Triangles::getV2() const
{
    return v2;
}

const Vector4f* Triangles::getList() const
{
    return vertices;
}

void Triangles::setColor(int index, float r, float g, float b){
    color[index].x = r;
    color[index].y = g;
    color[index].z = b;
}

void Triangles::setColors(const std::array<Vector3f, 3>& colors){
    for(int i = 0; i < 3; i++){
        color[i] = colors[i];
    }
}