#pragma once

#include "Math/Vector.hpp"

struct Vertex
{
    Vector4f position;
    Vector3f normPosition;
    Vector3f color;
    Vector3f normal;
    Vector3f worldPos;
    Vector2f uv;

    Vertex() = default;

    Vertex(const Vector4f& position_, const Vector3f& color_, const Vector3f& normal_, const Vector3f& _worldPos, const Vector2f& _uv) : position(position_), color(color_), normal(normal_), worldPos(_worldPos), uv(_uv) {}

    Vertex(const Vector3f& _normPosition, const Vector3f& _color, const Vector3f& _normal) : normPosition(_normPosition), color(_color), normal(_normal) {}
};

