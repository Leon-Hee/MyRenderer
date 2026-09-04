#pragma once

#include "Math/Vector.hpp"

class Triangles {
public:
    Vector3f color[3];
    Triangles();
    Triangles(const Vector4f& v0,
              const Vector4f& v1,
              const Vector4f& v2);

    Vector4f getV0() const;
    Vector4f getV1() const;
    Vector4f getV2() const;
    void setColor(int index, float r, float g, float b);

    void setColors(const std::array<Vector3f, 3>& colors);


    const Vector4f* getList() const;

private:
    Vector4f v0;
    Vector4f v1;
    Vector4f v2;

    Vector4f vertices[3];
};