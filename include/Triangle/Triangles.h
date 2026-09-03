#pragma once

#include "Math/Vector.hpp"
#include "Color.hpp"

class Triangles {
public:
    Color c;
    Triangles();
    Triangles(const Vector4f& v0,
              const Vector4f& v1,
              const Vector4f& v2);

    Vector4f getV0() const;
    Vector4f getV1() const;
    Vector4f getV2() const;


    const Vector4f* getList() const;

private:
    Vector4f v0;
    Vector4f v1;
    Vector4f v2;

    Vector4f vertices[3];
};