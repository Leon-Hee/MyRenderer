#include "Shadow/ShadowMap.h"

#include "Transform/Transform.h"

#include <algorithm>
#include <cmath>

ShadowMap::ShadowMap(int width_, int height_)
    : width(width_),
      height(height_),
      depth(width_ * height_, 1.0f)
{
}

void ShadowMap::clear()
{
    std::fill(depth.begin(), depth.end(), 1.0f);
}

void ShadowMap::setDepth(int x, int y, float value)
{
    depth[y * width + x] = value;
}

float ShadowMap::getDepth(int x, int y) const
{
    return depth[y * width + x];
}

int ShadowMap::getWidth() const
{
    return width;
}

int ShadowMap::getHeight() const
{
    return height;
}

void ShadowMap::renderTriangle(
    const Triangles& triangle,
    const Mat4& lightMVP)
{
    Vector4f v0 = lightMVP * triangle.getV0();
    Vector4f v1 = lightMVP * triangle.getV1();
    Vector4f v2 = lightMVP * triangle.getV2();

    Vector3f ndc0 = perspectiveDivide(v0);
    Vector3f ndc1 = perspectiveDivide(v1);
    Vector3f ndc2 = perspectiveDivide(v2);

    Vector3f p0(
        (ndc0.x * 0.5f + 0.5f) * width,
        (ndc0.y * 0.5f + 0.5f) * height,
        ndc0.z * 0.5f + 0.5f
    );

    Vector3f p1(
        (ndc1.x * 0.5f + 0.5f) * width,
        (ndc1.y * 0.5f + 0.5f) * height,
        ndc1.z * 0.5f + 0.5f
    );

    Vector3f p2(
        (ndc2.x * 0.5f + 0.5f) * width,
        (ndc2.y * 0.5f + 0.5f) * height,
        ndc2.z * 0.5f + 0.5f
    );

    int minX = std::max(
        0,
        static_cast<int>(
            std::floor(std::min({p0.x, p1.x, p2.x}))
        )
    );

    int maxX = std::min(
        width - 1,
        static_cast<int>(
            std::ceil(std::max({p0.x, p1.x, p2.x}))
        )
    );

    int minY = std::max(
        0,
        static_cast<int>(
            std::floor(std::min({p0.y, p1.y, p2.y}))
        )
    );

    int maxY = std::min(
        height - 1,
        static_cast<int>(
            std::ceil(std::max({p0.y, p1.y, p2.y}))
        )
    );

    Vector2f a(p0.x, p0.y);
    Vector2f b(p1.x, p1.y);
    Vector2f c(p2.x, p2.y);

    float area = crossProduct(b - a, c - a);

    if (std::abs(area) < 1e-6f)
    {
        return;
    }

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            Vector2f p(
                x + 0.5f,
                y + 0.5f
            );

            float alpha =
                crossProduct(b - p, c - p) / area;

            float beta =
                crossProduct(c - p, a - p) / area;

            float gamma =
                1.0f - alpha - beta;

            if (alpha < 0.0f ||
                beta < 0.0f ||
                gamma < 0.0f)
            {
                continue;
            }

            float z =
                alpha * p0.z +
                beta * p1.z +
                gamma * p2.z;

            if (z < getDepth(x, y))
            {
                setDepth(x, y, z);
            }
        }
    }
}