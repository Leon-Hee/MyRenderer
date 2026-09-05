#include <iostream>

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Triangle/Triangles.h"
#include "Math/Vector.hpp"
#include "Math/Mat.hpp"
#include "Transform/Transform.h"

int main()
{
    const int width = 800;
    const int height = 800;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear();
    depthbuffer.clear();

    // ==============================
    // 1. Perspective Projection
    // ==============================

    float fov = 60.0f;
    float aspect = static_cast<float>(width) / height;
    float zNear = 0.1f;
    float zFar = 100.0f;

    Mat4 projection = perspective(
        fov,
        aspect,
        zNear,
        zFar
    );

    // ==============================
    // 2. Triangle
    // ==============================

    // 近处三角形
    Triangles nearTri(
        Vector3f(1.0f, -1.0f, -2.0f),
        Vector3f( 2.0f, -1.0f, -2.0f),
        Vector3f( 1.0f,  1.0f, -2.0f)
    );

    // 远处三角形
    Triangles farTri(
        Vector3f(-1.0f, -1.0f, -6.0f),
        Vector3f(-2.0f, -1.0f, -6.0f),
        Vector3f( -1.0f,  1.0f, -6.0f)
    );

    // ==============================
    // 3. Render
    // ==============================

    render::RenderTriangles(
        nearTri,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        farTri,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    // ==============================
    // 4. Save
    // ==============================

    framebuffer.save("perspective_test.ppm");

    std::cout << "Perspective test finished!\n";
    std::cout << "Output: perspective_test.ppm\n";

    return 0;
}