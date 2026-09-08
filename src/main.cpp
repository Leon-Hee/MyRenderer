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

    Mat4 model =
        translate(0.0f, 0.0f, -1.0f);

    Mat4 MVP = projection * model;

    // =========================
    // Triangle
    //
    // 两个顶点很近
    // 一个顶点很远
    //
    // 产生明显不同的 Clip-Space W
    // =========================

    Vector3f v0(
        -0.8f,
        -0.8f,
         0.0f
    );

    Vector3f v1(
         0.8f,
        -0.8f,
         0.0f
    );

    Vector3f v2(
         0.0f,
         0.8f,
        -8.0f
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
        << "========== Perspective Interpolation Test ==========\n";

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
        "perspective_interpolation_1.ppm"
    );

    std::cout
        << "Perspective interpolation test finished!\n";

    return 0;
}