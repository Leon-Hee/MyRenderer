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

    // 深灰色材质，让白色高光更加明显
    const Vector3f materialColor(
        0.22f,
        0.22f,
        0.22f
    );

    std::vector<Triangles> triangles;

    // ============================================================
    // 2. Icosahedron
    //
    // 一个 20 面三角形多面体
    // 比 Cube 更适合观察 Specular
    // ============================================================

    constexpr float phi = 1.61803398875f;

    std::vector<Vector3f> vertices =
    {
        // (0, ±1, ±phi)
        Vector3f(0, -1,  phi),
        Vector3f(0,  1,  phi),
        Vector3f(0, -1, -phi),
        Vector3f(0,  1, -phi),

        // (±1, ±phi, 0)
        Vector3f(-1,  phi, 0),
        Vector3f( 1,  phi, 0),
        Vector3f(-1, -phi, 0),
        Vector3f( 1, -phi, 0),

        // (±phi, 0, ±1)
        Vector3f( phi, 0, -1),
        Vector3f( phi, 0,  1),
        Vector3f(-phi, 0, -1),
        Vector3f(-phi, 0,  1)
    };

    // 归一化到单位球面
    for (auto& v : vertices)
    {
        v.normalize();
    }

    // ============================================================
    // 3. Icosahedron faces
    // ============================================================

    const int faces[20][3] =
    {
        {0, 11, 5},
        {0, 5, 1},
        {0, 1, 7},
        {0, 7, 10},
        {0, 10, 11},

        {1, 5, 9},
        {5, 11, 4},
        {11, 10, 2},
        {10, 7, 6},
        {7, 1, 8},

        {3, 9, 4},
        {3, 4, 2},
        {3, 2, 6},
        {3, 6, 8},
        {3, 8, 9},

        {4, 9, 5},
        {2, 4, 11},
        {6, 2, 10},
        {8, 6, 7},
        {9, 8, 1}
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
        // 当前先使用面法线。
        // 这样可以看到明显的多面体结构。
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
        3.5f,
        2.5f,
        5.5f
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

    Light light(
        Vector3f(3.0f, 4.0f, 2.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        1.0f,      // intensity
        0.03f      // ambient
    );

    // 比 8 更集中，比 64 更容易看到
    light.shininess = 32.0f;

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

    framebuffer.save("polyhedron_specular_test.ppm");

    std::cout << "====================================\n";
    std::cout << "Polyhedron Blinn-Phong test finished.\n";
    std::cout << "Saved: polyhedron_specular_test.ppm\n";
    std::cout << "====================================\n";

    return 0;
}