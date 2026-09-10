#pragma once

#include "Triangle/Triangles.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Shader/Light.h"
#include "Texture/Texture.h"
#include "Shader/Material.h"

class Rasterizer
{
private:
    bool isInside(const float x, const float y, const Triangles& triangles) const;
    Vector3f barycentric(const float x, const float y , const Triangles& triangles) const;
public:
    Rasterizer() = default;
    void drawTriangles(const Triangles& triangles, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Light& light, const Vector3f& cameraPos, const Material& material) const ;
};

