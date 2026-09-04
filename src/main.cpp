#include <iostream>


#include "Math/Vector.hpp"

#include "Math/Mat.hpp"

#include "Framebuffer/Framebuffer.h"

#include "DepthBuffer/Depthbuffer.h"

#include "Triangle/Triangles.h"

#include "Rasterizer/Rasterizer.h"

#include "Transform/Transform.h"

#include "Transform/Viewport.h"

int main() {

    const int width = 800;
    const int height = 600;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    Rasterizer rasterizer;

    framebuffer.clear(Vector3f(0.0f));
    depthbuffer.clear();

    // =========================
    // Camera
    // =========================

    Vector3f eye(0.0f, 0.0f, 5.0f);
    Vector3f center(0.0f, 0.0f, 0.0f);
    Vector3f up(0.0f, 1.0f, 0.0f);

    Mat4 view = lookAt(eye, center, up);

    Mat4 projection = perspective(
        60.0f,
        static_cast<float>(width) / height,
        0.1f,
        100.0f
    );

    Mat4 model = Mat4::Identity();

    Mat4 mvp = getMVP(model, view, projection);


    // =========================
    // Clip -> Screen
    // =========================

    auto toScreen = [&](const Vector4f& vertex) {

        Vector4f clip = mvp * vertex;

        Vector3f ndc(
            clip.x / clip.w,
            clip.y / clip.w,
            clip.z / clip.w
        );

        Vector3f screen(
            (ndc.x + 1.0f) * 0.5f * width,
            (ndc.y + 1.0f) * 0.5f * height,
            (ndc.z + 1.0f) * 0.5f
        );

        return Vector4f(
            screen.x,
            screen.y,
            screen.z,
            clip.w
        );
    };


    // =========================================================
    // Red triangle
    // 后面：z = -1
    // =========================================================

    Vector4f red0 = toScreen(
        Vector4f(-1.8f, -1.4f, -1.0f, 1.0f)
    );

    Vector4f red1 = toScreen(
        Vector4f(1.8f, -1.4f, -1.0f, 1.0f)
    );

    Vector4f red2 = toScreen(
        Vector4f(0.0f, 1.8f, -1.0f, 1.0f)
    );


    Triangles redTriangle(
        red0,
        red1,
        red2
    );

    redTriangle.color[0] = Vector3f(1.0f, 0.0f, 0.0f);
    redTriangle.color[1] = Vector3f(1.0f, 0.0f, 0.0f);
    redTriangle.color[2] = Vector3f(1.0f, 0.0f, 0.0f);


    // =========================================================
    // Blue triangle
    // 前面：z = 0
    // =========================================================

    Vector4f blue0 = toScreen(
        Vector4f(-0.8f, -0.6f, 0.0f, 1.0f)
    );

    Vector4f blue1 = toScreen(
        Vector4f(1.5f, -0.6f, 0.0f, 1.0f)
    );

    Vector4f blue2 = toScreen(
        Vector4f(0.4f, 0.8f, 0.0f, 1.0f)
    );


    Triangles blueTriangle(
        blue0,
        blue1,
        blue2
    );

    blueTriangle.color[0] = Vector3f(0.0f, 0.0f, 1.0f);
    blueTriangle.color[1] = Vector3f(0.0f, 0.0f, 1.0f);
    blueTriangle.color[2] = Vector3f(0.0f, 0.0f, 1.0f);


    // =========================
    // Print screen coordinates
    // =========================

    std::cout << "========== RED ==========\n";

    std::cout << "v0: "
              << red0.x << " "
              << red0.y << " "
              << red0.z << "\n";

    std::cout << "v1: "
              << red1.x << " "
              << red1.y << " "
              << red1.z << "\n";

    std::cout << "v2: "
              << red2.x << " "
              << red2.y << " "
              << red2.z << "\n";


    std::cout << "\n========== BLUE ==========\n";

    std::cout << "v0: "
              << blue0.x << " "
              << blue0.y << " "
              << blue0.z << "\n";

    std::cout << "v1: "
              << blue1.x << " "
              << blue1.y << " "
              << blue1.z << "\n";

    std::cout << "v2: "
              << blue2.x << " "
              << blue2.y << " "
              << blue2.z << "\n";


    // =========================
    // Print depth
    // =========================

    std::cout << "\n========== DEPTH ==========\n";

    std::cout << "Red depth: "
              << red0.z << " "
              << red1.z << " "
              << red2.z << "\n";

    std::cout << "Blue depth: "
              << blue0.z << " "
              << blue1.z << " "
              << blue2.z << "\n";


    // =========================
    // Draw
    // =========================

    std::cout << "\n========== DRAW ==========\n";

    // 后面的红三角先画
    rasterizer.drawTriangles(
        redTriangle,
        framebuffer,
        depthbuffer
    );

    // 前面的蓝三角后画
    rasterizer.drawTriangles(
        blueTriangle,
        framebuffer,
        depthbuffer
    );


    std::cout << "Depth test finished.\n";


    // =========================
    // Save
    // =========================

    framebuffer.save("depth_test.ppm");

    return 0;
}