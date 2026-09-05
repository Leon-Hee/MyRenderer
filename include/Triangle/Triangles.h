#pragma once

#include "Math/Vector.hpp"

class Triangles {
public:
    Vector3f color[3];
    Triangles();
    Triangles(const Vector4f& v0,
              const Vector4f& v1,
              const Vector4f& v2);

    Triangles(const Vector3f& vert0_,
              const Vector3f& vert1_,
              const Vector3f& vert2_);

    Vector4f getV0() const;
    Vector4f getV1() const;
    Vector4f getV2() const;
    void setColor(int index, float r, float g, float b);

    void setColors(const std::array<Vector3f, 3>& colors);

    bool isVec4 = false;

    Triangles toVec4T(const Triangles& t);

    const Vector4f* getList() const;
    const Vector3f* getListVec3() const;


    Vector3f vert0;
    Vector3f vert1;
    Vector3f vert2;

private:
    Vector4f v0;
    Vector4f v1;
    Vector4f v2;

    Vector4f vertices[3];
    Vector3f verts[3];
};