#pragma once

#include "Math/Vector.hpp"
#include "Texture/Texture.h"

class Material{
public:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
    const Texture* diffuseTexture;
};