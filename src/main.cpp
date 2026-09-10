#include <iostream>
#include <vector>

#include "objLoader/objLoader.h"

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Transform/Transform.h"
#include "Shader/Light.h"
#include "Shader/Material.h"

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
    // 2. Load OBJ
    // =========================

    std::vector<Triangles> model =
        OBJLoader::load(
            "obj/african_head/african_head.obj"
        );

    std::cout << "Loaded triangles: "
              << model.size()
              << std::endl;


    // =========================
    // 3. Model / View / Projection
    // =========================

    Vector3f cameraPos(
        0.0f,
        0.0f,
        3.0f
    );

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
    // 4. Light
    // =========================

    Light light(
        Vector3f(3.0f, 4.0f, 3.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        1.0f,
        0.2f,
        32.0f
    );

    light.ambient_intensity = 0.1f;


    // =========================
    // 5. Material
    // =========================

    Texture texture(
    "obj/african_head/african_head_diffuse.tga"
);

Material material;

material.diffuseColor = Vector3f(
    1.0f,
    1.0f,
    1.0f
);

material.specularColor = Vector3f(
    0.2f,
    0.2f,
    0.2f
);

material.shininess = 16.0f;

material.diffuseTexture = &texture;


    // =========================
    // 6. Render
    // =========================

    for (Triangles& triangle : model)
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
            cameraPos,
            material
        );
    }


    // =========================
    // 7. Save
    // =========================

    framebuffer.save(
        "african_head_test.ppm"
    );

    std::cout << "African head render finished."
              << std::endl;

    return 0;
}