#include <iostream>
#include <vector>
#include <cmath>

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Triangle/Triangles.h"
#include "Math/Vector.hpp"
#include "Math/Mat.hpp"
#include "Transform/Transform.h"
#include "Shader/Light.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    // ============================================================
    // 1. Material
    // ============================================================

    // 深灰色材质
    // 用深色材质可以让白色 Specular 高光更加明显
    const Vector3f materialColor(
        0.22f,
        0.22f,
        0.22f
    );

    std::vector<Triangles> triangles;

    // ============================================================
    // 2. Cube vertices
    //
    //        7--------6
    //       /|       /|
    //      4--------5 |
    //      | |      | |
    //      | 3------|-2
    //      |/       |/
    //      0--------1
    //
    // ============================================================

    const float s = 1.0f;

    std::vector<Vector3f> vertices =
    {
        Vector3f(-s, -s, -s), // 0
        Vector3f( s, -s, -s), // 1
        Vector3f( s,  s, -s), // 2
        Vector3f(-s,  s, -s), // 3

        Vector3f(-s, -s,  s), // 4
        Vector3f( s, -s,  s), // 5
        Vector3f( s,  s,  s), // 6
        Vector3f(-s,  s,  s)  // 7
    };

    // ============================================================
    // 3. Cube faces
    //
    // 每个面由两个三角形组成
    //
    // Front  : z = +s
    // Back   : z = -s
    // Left   : x = -s
    // Right  : x = +s
    // Top    : y = +s
    // Bottom : y = -s
    //
    // ============================================================

    const int faces[12][3] =
    {
        // Front
        {4, 5, 6},
        {4, 6, 7},

        // Back
        {0, 2, 1},
        {0, 3, 2},

        // Left
        {0, 4, 7},
        {0, 7, 3},

        // Right
        {1, 2, 6},
        {1, 6, 5},

        // Top
        {3, 7, 6},
        {3, 6, 2},

        // Bottom
        {0, 1, 5},
        {0, 5, 4}
    };

    // ============================================================
    // 4. Create triangles
    // ============================================================

    for (const auto& face : faces)
    {
        Vector3f v0 = vertices[face[0]];
        Vector3f v1 = vertices[face[1]];
        Vector3f v2 = vertices[face[2]];

        triangles.emplace_back(v0, v1, v2);

        // --------------------------------------------------------
        // Flat normal
        //
        // 一个面的两个三角形使用相同的法线
        // --------------------------------------------------------

        Vector3f normal =
            crossProduct(v1 - v0, v2 - v0).normalized();

        triangles.back().setNormal(
            normal,
            normal,
            normal
        );

        triangles.back().setColors({
            materialColor,
            materialColor,
            materialColor
        });
    }

    // ============================================================
    // 5. Model
    // ============================================================

    Mat4 M = Mat4::Identity();

    // ============================================================
    // 6. Camera
    // ============================================================

    Vector3f cameraPos(
        4.0f,
        3.0f,
        6.0f
    );

    Mat4 V = lookAt(
        cameraPos,
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 0.0f)
    );

    // ============================================================
    // 7. Projection
    // ============================================================

    Mat4 P = perspective(
        45.0f,
        static_cast<float>(width) / height,
        0.1f,
        100.0f
    );

    // ============================================================
    // 8. MVP
    // ============================================================

    Mat4 MVP = getMVP(
        M,
        V,
        P
    );

    // ============================================================
    // 9. Light
    // ============================================================

    // 放在摄像机右上方
    // 这样比较容易观察 Specular
    float shininess = 128.0f;
    Light light(
        Vector3f(-1.0f, 2.0f, 2.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        3.0f,      // intensity
        0.3f,      // ambient
        shininess
    );

    // Blinn-Phong shininess
    //
    // 8   -> 高光很宽
    // 32  -> 比较明显
    // 64  -> 更集中
    // 128 -> 非常集中

    // ============================================================
    // 10. Render
    // ============================================================

    for (Triangles& triangle : triangles)
    {
        render::RenderTriangles(
            triangle,
            framebuffer,
            depthbuffer,
            MVP,
            width,
            height,
            M,
            V,
            light,
            cameraPos
        );
    }

    // ============================================================
    // 11. Save
    // ============================================================

    framebuffer.save("cube_specular_test.ppm");

    std::cout << "====================================\n";
    std::cout << "Cube Blinn-Phong test finished.\n";
    std::cout << "Saved: cube_specular_test.ppm\n";
    std::cout << "====================================\n";

    return 0;
}