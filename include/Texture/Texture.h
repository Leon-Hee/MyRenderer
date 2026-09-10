#pragma once

#include "Math/Vector.hpp"
#include "string"

class Texture{
public:
    Texture();
    Texture(const std::string& path);
    Vector3f sample(const Vector2f& uv) const;
    ~Texture();
private:
    unsigned char* data;
    int width;
    int height;
    int channels;
};