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

    // =========================
    // Projection
    // =========================

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

    // =========================
    // 1. Front Face
    // 左下
    // =========================

    Triangles front1(
        Vector3f(-3.0f, -1.0f, -3.0f),
        Vector3f(-1.0f, -1.0f, -3.0f),
        Vector3f(-2.0f,  1.0f, -3.0f)
    );

    // =========================
    // 2. Back Face
    // 反转 1 的 winding
    // =========================

    /*Triangles back1(
        Vector3f(1.0f, -1.0f, -3.0f),
        Vector3f(0.0f,  1.0f, -3.0f),
        Vector3f(2.0f, -1.0f, -3.0f)
    );*/

    Triangles back1(
    Vector3f(1.0f, -1.0f, -3.0f),
    Vector3f(2.0f, -1.0f, -3.0f),
    Vector3f(0.0f,  1.0f, -3.0f)
    );



    // =========================
    // 3. Front Face
    // 右上
    // =========================

    Triangles front2(
        Vector3f(1.0f, 1.0f, -3.0f),
        Vector3f(3.0f, 1.0f, -3.0f),
        Vector3f(2.0f, 3.0f, -3.0f)
    );

    // =========================
    // 4. Back Face
    // =========================

    Triangles back2(
        Vector3f(4.0f, 1.0f, -3.0f),
        Vector3f(5.0f, 3.0f, -3.0f),
        Vector3f(6.0f, 1.0f, -3.0f)
    );

    // =========================
    // 5. Very Thin Triangle
    // 测试 EPSILON
    // =========================

    Triangles thin(
        Vector3f(-3.0f, 3.0f, -3.0f),
        Vector3f(-1.0f, 3.0f, -3.0f),
        Vector3f(-2.0f, 3.000001f, -3.0f)
    );

    // =========================
    // 6. Degenerate Triangle
    // 三点共线
    // =========================

    Triangles degenerate(
        Vector3f(3.0f, -3.0f, -3.0f),
        Vector3f(4.0f, -2.0f, -3.0f),
        Vector3f(5.0f, -1.0f, -3.0f)
    );

    // =========================
    // Render
    // =========================

    render::RenderTriangles(
        front1,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        back1,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        front2,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        back2,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        thin,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    render::RenderTriangles(
        degenerate,
        framebuffer,
        depthbuffer,
        projection,
        width,
        height
    );

    // =========================
    // Save
    // =========================

    framebuffer.save("culling_test.ppm");

    std::cout << "Back-face culling test finished!\n";
    std::cout << "Output: culling_test.ppm\n";

    return 0;
}