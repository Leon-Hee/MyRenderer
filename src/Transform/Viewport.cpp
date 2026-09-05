#include "Transform/Viewport.h"

Viewport::Viewport(int width_, int height_): width(width_), height(height_) {}

Vector3f Viewport::transform(const Vector3f& ndc, int width, int height){
    float x = (ndc.x + 1.0f) * 0.5f * width;
    float y = (ndc.y + 1.0f) * 0.5f * height;
    float z = (ndc.z + 1.0f) * 0.5f;
    return Vector3f(x, y, z);
}