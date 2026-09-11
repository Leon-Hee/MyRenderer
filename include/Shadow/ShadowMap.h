#pragma once

#include <vector>

#include "Math/Mat.hpp"
#include "Triangle/Triangles.h"

class ShadowMap {
public:
    ShadowMap(int width, int height);

    void clear();

    void setDepth(int x, int y, float depth);

    float getDepth(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    void renderTriangle(
        const Triangles& triangle,
        const Mat4& lightMVP
    );

private:
    int width;
    int height;

    std::vector<float> depth;
};