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
    constexpr int width = 800;
    constexpr int height = 800;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear();
    depthbuffer.clear();

    // =========================
    // Projection
    // =========================

    constexpr float fov = 60.0f;
    constexpr float zNear = 0.1f;
    constexpr float zFar = 100.0f;

    const float aspect =
        static_cast<float>(width) /
        static_cast<float>(height);

    Mat4 projection = perspective(
        fov,
        aspect,
        zNear,
        zFar
    );

    // =========================
    // Model
    // =========================

    // 放到相机前方
    Mat4 model =
        translate(0.0f, 0.0f, -1.0f);

    Mat4 MVP = projection * model;

    // =========================
    // Triangle
    //
    // 让一个顶点非常靠近 Near Plane
    //
    // v0: 接近 Near Plane
    // v1/v2: 正常在视锥体内部
    //
    // 这个版本先避免直接让 z 穿过
    // Near Plane 太极端的位置。
    // =========================

    Vector3f v0(
        -0.8f,
        -0.8f,
        1.85f
    );

    Vector3f v1(
         0.8f,
        -0.8f,
        0.0f
    );

    Vector3f v2(
         0.0f,
         0.8f,
         0.0f
    );

    // =========================
    // Colors
    // =========================

    Vector3f red(
        1.0f,
        0.0f,
        0.0f
    );

    Vector3f green(
        0.0f,
        1.0f,
        0.0f
    );

    Vector3f blue(
        0.0f,
        0.0f,
        1.0f
    );

    // =========================
    // Triangle
    // =========================

    Triangles triangle(
        v0,
        v1,
        v2
    );

    triangle.setColors({
        red,
        green,
        blue
    });

    // =========================
    // Debug
    // =========================

    std::cout
        << "========== Near Clip Test ==========\n";

    std::cout
        << "v0 Model: "
        << v0.x << " "
        << v0.y << " "
        << v0.z << "\n";

    std::cout
        << "v1 Model: "
        << v1.x << " "
        << v1.y << " "
        << v1.z << "\n";

    std::cout
        << "v2 Model: "
        << v2.x << " "
        << v2.y << " "
        << v2.z << "\n";

    // =========================
    // Render
    // =========================

    render::RenderTriangles(
        triangle,
        framebuffer,
        depthbuffer,
        MVP,
        width,
        height
    );

    // =========================
    // Save
    // =========================

    framebuffer.save(
        "near_clip_gradient.ppm"
    );

    std::cout
        << "Near clip gradient test finished!\n";

    return 0;
}