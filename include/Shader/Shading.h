#pragma once

#include "Shader/Fragment.h"
#include "Shader/Light.h"

class Shading{
public:
    Vector3f shade(const Fragment& fragment, const Light& light, Light::Type lightType);


};