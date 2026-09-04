#pragma once

#include "Triangle/Triangles.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"

class Rasterizer
{
private:
    bool isInside(const float x, const float y, const Triangles& triangles) const;
    Vector3f barycentric(const float x, const float y , const Triangles& triangles) const;
public:
    Rasterizer() = default;
    void drawTriangles(const Triangles& triangles, Framebuffer& framebuffer, Depthbuffer& depthbuffer) const ;
};

