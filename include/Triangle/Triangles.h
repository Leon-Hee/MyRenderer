#pragma once

#include "Math/Vector.hpp"
#include "Math/Mat.hpp"

class Triangles {
public:
    Vector3f color[3];
    Vector3f normal[3];
    Vector3f position[3];//World Space
    Vector2f uv[3];
    float invW[3]{1.0f, 1.0f, 1.0f};
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

    Vector3f getNormal(int index);
    void setNormal(const Vector3f& normal_1, const Vector3f& normal_2, const Vector3f& normal_3);
    Triangles tranNormal(const Triangles& t, Mat4 M);

    void setUV(const Vector2f& uv0, const Vector2f& uv1, const Vector2f& uv2);
    Vector2f getUV(int index);

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