#pragma once

#include "Rasterizer/Rasterizer.h"
#include "Math/Mat.hpp"
#include "Math/Vector.hpp"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"

namespace render{
    void RenderTriangles(Triangles& t1, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Mat4 MVP, int width, int height);
    bool isFront(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
}