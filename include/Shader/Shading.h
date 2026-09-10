#pragma once

#include "Shader/Fragment.h"
#include "Shader/Light.h"
#include "Shader/Material.h"

class Shading{
public:
    Vector3f shade(const Fragment& fragment, const Light& light, const Material& material,Light::Type lightType);


};