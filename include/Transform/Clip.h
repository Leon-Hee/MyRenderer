#pragma once

#include <vector>
#include "Math/Mat.hpp"
#include "Triangle/Triangles.h"

namespace Clip{
    enum class ClipPlane {
        Left,
        Right,
        Up,
        Down,
        Front,
        Back
    };

    bool inside(const Vector4f& v, ClipPlane clipPlane);

    Vector4f intersect(const Vector4f& a, const Vector4f& b, ClipPlane clipPlane);

    std::vector<Vector4f> clipSinglePlane (const std::vector<Vector4f>& polygon, ClipPlane clipPlane);

    std::vector<Vector4f> clipTriangle(const Triangles& t);

    std::vector<Triangles> toTriangleList(const std::vector<Vector4f> polygon);
}
