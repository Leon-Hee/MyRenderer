#pragma once

#include "Math/Vector.hpp"

struct Vertex
{
    Vector4f position;
    Vector3f normPosition;
    Vector3f color;

    Vertex() = default;

    Vertex(const Vector4f& position_, const Vector3f& color_) : position(position_), color(color_) {}

    Vertex(const Vector3f& _normPosition, const Vector3f& _color) : normPosition(_normPosition), color(_color) {}
};

