#pragma once

#include "Rasterizer/Rasterizer.h"
#include "Math/Mat.hpp"
#include "Math/Vector.hpp"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Shader/Light.h"

namespace render{
    void RenderTriangles(Triangles& t1, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Mat4& MVP, int width, int height, const Mat4& M, const Mat4& V, const Light& light, const Vector3f& cameraPos);
    bool isFront(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
}