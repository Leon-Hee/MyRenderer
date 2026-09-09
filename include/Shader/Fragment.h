#pragma once

#include "Math/Vector.hpp"

class Fragment{
public:
    Vector3f position;
    Vector3f normal;
    Vector3f color;
    Vector3f camera_position;
    Fragment(const Vector3f& _position, const Vector3f& _normal, const Vector3f& _color, const Vector3f& _camera_position) : position(_position), normal(_normal), color(_color), camera_position(_camera_position) {}
};