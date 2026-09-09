#include "Shader/Shading.h"
#include <algorithm>

Vector3f Shading::shade(const Fragment& fragment, const Light& light, Light::Type lightType){
    if(lightType == Light::Type::Ambient){
        return fragment.color * light.ambient_intensity * light.color;
    }else if(lightType == Light::Type::Diffuse){
        Vector3f lightPos = light.position - fragment.position;
        lightPos.normalize();
        Vector3f normal = fragment.normal;
        normal.normalize();
        float diffuse = std::max(0.0f, dotProduct(lightPos, normal));
        return light.intensity * light.color * diffuse * fragment.color;

    }else if(lightType == Light::Type::Specular){
        Vector3f lightPos = light.position - fragment.position;
        lightPos.normalize();
        Vector3f viewPos = fragment.camera_position - fragment.position;
        viewPos.normalize();
        Vector3f normal = fragment.normal;
        normal.normalize();
        Vector3f half = (lightPos + viewPos).normalize();
        float specular = std::pow(std::max(0.0f, dotProduct(half, normal)), light.shininess);
        return light.intensity * specular * light.color;
    }
    return Vector3f(0.0f, 0.0f, 0.0f);
}