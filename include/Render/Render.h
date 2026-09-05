#pragma once

#include "Rasterizer/Rasterizer.h"
#include "Math/Mat.hpp"
#include "Math/Vector.hpp"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"

namespace render{
    void RenderTriangles(Triangles& t1, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Mat4 MVP, int width, int height);
}