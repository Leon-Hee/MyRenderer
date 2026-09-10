#include <iostream>

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Triangle/Triangles.h"
#include "Transform/Transform.h"
#include "Shader/Light.h"
#include "Texture/Texture.h"

int main()
{
    // =========================
    // 1. Framebuffer / Depthbuffer
    // =========================

    const int width = 800;
    const int height = 800;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear(
        Vector3f(0.05f, 0.05f, 0.05f)
    );

    depthbuffer.clear();


    // =========================
    // 2. Model / View / Projection
    // =========================

    Vector3f cameraPos(0.0f, 0.0f, 5.0f);

    Mat4 M = Mat4::Identity();

    Mat4 V = lookAt(
        cameraPos,
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 0.0f)
    );

    Mat4 P = perspective(
        60.0f,
        static_cast<float>(width) / height,
        0.1f,
        100.0f
    );

    Mat4 MVP = P * V * M;


    // =========================
    // 3. Light
    // =========================

    Light light(
        Vector3f(3.0f, 4.0f, 3.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        1.0f,
        0.2f,
        32
    );

    light.ambient_intensity = 0.1f;
    light.shininess = 32.0f;


    // =========================
    // 4. Texture
    // =========================

    Texture containerTexture("assets/container.jpg");
    Texture smileTexture("assets/smile.png");


    // =========================
    // 5. Same Front Face
    // =========================

    const float s = 1.0f;

    Vector3f normal(0.0f, 0.0f, 1.0f);


    // =========================================================
    // Triangle 1
    // =========================================================

    Triangles t1(
        Vector4f(-s, -s, s, 1.0f),
        Vector4f( s, -s, s, 1.0f),
        Vector4f( s,  s, s, 1.0f)
    );

    t1.setColors({
        Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(1.0f, 1.0f, 1.0f)
    });

    t1.setNormal(normal, normal, normal);

    t1.setUV(
        Vector2f(0.0f, 0.0f),
        Vector2f(1.0f, 0.0f),
        Vector2f(1.0f, 1.0f)
    );


    // =========================================================
    // Triangle 2
    // =========================================================

    Triangles t2(
        Vector4f(-s, -s, s, 1.0f),
        Vector4f( s,  s, s, 1.0f),
        Vector4f(-s,  s, s, 1.0f)
    );

    t2.setColors({
        Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(1.0f, 1.0f, 1.0f)
    });

    t2.setNormal(normal, normal, normal);

    t2.setUV(
        Vector2f(0.0f, 0.0f),
        Vector2f(1.0f, 1.0f),
        Vector2f(0.0f, 1.0f)
    );


    // =========================================================
    // 第一次：Container
    // =========================================================

    render::RenderTriangles(
        t1,
        framebuffer,
        depthbuffer,
        MVP,
        width,
        height,
        M,
        V,
        light,
        cameraPos,
        containerTexture
    );

    render::RenderTriangles(
        t2,
        framebuffer,
        depthbuffer,
        MVP,
        width,
        height,
        M,
        V,
        light,
        cameraPos,
        containerTexture
    );

    depthbuffer.clear();
    // =========================================================
    // 第二次：Smile
    // =========================================================

    render::RenderTriangles(
        t1,
        framebuffer,
        depthbuffer,
        MVP,
        width,
        height,
        M,
        V,
        light,
        cameraPos,
        smileTexture
    );

    render::RenderTriangles(
        t2,
        framebuffer,
        depthbuffer,
        MVP,
        width,
        height,
        M,
        V,
        light,
        cameraPos,
        smileTexture
    );


    // =========================
    // 6. Save
    // =========================

    framebuffer.save("same_face_two_texture_test.ppm");

    std::cout << "Same face two texture test finished."
              << std::endl;

    return 0;
}