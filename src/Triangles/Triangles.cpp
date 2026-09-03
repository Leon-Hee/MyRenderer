#include "Triangles.h"

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