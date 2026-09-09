#pragma once

#include"Math/Vector.hpp"

class Light{
public:
    Vector3f position;
    Vector3f color;
    float ambient_intensity;
    float intensity;
    float shininess;
    Light(const Vector3f& _position, const Vector3f& _color, const float _intensity, const float _ambient_intensity) : position(_position), color(_color), intensity(_intensity), ambient_intensity(_ambient_intensity){}
    enum class Type{
        Ambient,
        Diffuse,
        Specular,
    };
};