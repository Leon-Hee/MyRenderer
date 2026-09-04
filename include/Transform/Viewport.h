#pragma once

#include <Math/Vector.hpp>

class Viewport{
public:
    Viewport(int width, int height);

    Vector3f transform(const Vector3f& ndc) const;

private:
    int width;
    int height;

};