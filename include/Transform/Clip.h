#pragma once

#include <vector>
#include "Math/Mat.hpp"
#include "Triangle/Triangles.h"
#include "Struction/Vertex.hpp"

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

    Vertex intersect(const Vertex& a, const Vertex& b, ClipPlane clipPlane);

    std::vector<Vertex> clipSinglePlane (const std::vector<Vertex>& polygon, ClipPlane clipPlane);

    std::vector<Vertex> clipTriangle(const Triangles& t, bool whetherInterpolate);

    std::vector<Triangles> toTriangleList(const std::vector<Vertex> polygon);
}
