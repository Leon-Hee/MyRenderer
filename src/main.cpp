#include <iostream>

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Triangle/Triangles.h"
#include "Transform/Transform.h"
#include "Shader/Light.h"
#include "Shader/Material.h"
#include "Texture/Texture.h"

int main()
{
    const int width = 800;
    const int height = 800;

    // =========================
    // Framebuffer / Depthbuffer
    // =========================

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear(
        Vector3f(0.05f, 0.05f, 0.05f)
    );

    depthbuffer.clear();


    // =========================
    // Camera
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
    // Light
    // =========================

    Light light(
        Vector3f(3.0f, 4.0f, 3.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        1.0f,
        0.2f,
        8.0f
    );

    light.ambient_intensity = 0.12f;


    // =========================
    // Texture
    // =========================

    Texture containerTexture(
        "assets/container.jpg"
    );


    // =========================
    // Rough Material
    // =========================

    Material material;

    material.diffuseColor = Vector3f(
        1.0f,
        1.0f,
        1.0f
    );

    // 较暗的镜面反射
    material.specularColor = Vector3f(
        0.15f,
        0.15f,
        0.15f
    );

    // 越低越粗糙，高光越宽
    material.shininess = 8.0f;

    material.diffuseTexture = &containerTexture;


    // =========================
    // Front Face
    // =========================

    const float s = 1.0f;

    Vector3f normal(
        0.0f,
        0.0f,
        1.0f
    );


    // =========================
    // Triangle 1
    // =========================

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

    t1.setNormal(
        normal,
        normal,
        normal
    );

    t1.setUV(
        Vector2f(0.0f, 0.0f),
        Vector2f(1.0f, 0.0f),
        Vector2f(1.0f, 1.0f)
    );


    // =========================
    // Triangle 2
    // =========================

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

    t2.setNormal(
        normal,
        normal,
        normal
    );

    t2.setUV(
        Vector2f(0.0f, 0.0f),
        Vector2f(1.0f, 1.0f),
        Vector2f(0.0f, 1.0f)
    );


    // =========================
    // Render
    // =========================

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
        material
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
        material
    );


    // =========================
    // Save
    // =========================

    framebuffer.save(
        "rough_material_test.ppm"
    );

    std::cout << "Rough material test finished."
              << std::endl;

    return 0;
}