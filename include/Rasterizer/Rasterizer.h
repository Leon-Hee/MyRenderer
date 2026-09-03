#pragma once

#include "Triangles.h"
#include "Framebuffer.h"
#include "Depthbuffer.h"

class Rasterizer
{
private:
    bool isInside(const float x, const float y, const Triangles& triangles) const;
    Vector3f barycentric(const float x, const float y , const Triangles& triangles) const;
public:
    Rasterizer() = default;
    void drawTriangles(const Triangles& triangles, Framebuffer& framebuffer, Depthbuffer& depthbuffer) const ;
};

