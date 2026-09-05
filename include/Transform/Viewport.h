#pragma once

#include <Math/Vector.hpp>

class Viewport{
public:
    Viewport(int width, int height);

    static Vector3f transform(const Vector3f& ndc, int width, int height);

private:
    int width;
    int height;

};