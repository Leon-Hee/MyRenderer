#pragma once

#include "Math/Mat.hpp"
#include "Math/Vector.hpp"

enum Axis{
    X,
    Y,
    Z
};

Mat4 translate(float x, float y, float z);

Mat4 scale(float x, float y, float z);

Mat4 scale(float arg);

Mat4 rotate(Axis axis, float angle);

Mat4 lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);

Mat4 perspective(float fov, float aspect, float zNear, float zFar);

Mat4 getMVP(const Mat4& model, const Mat4& view, const Mat4& projection);

Vector3f perspectiveDivide(const Vector4f& clip);