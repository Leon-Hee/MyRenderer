#include <iostream>
#include <vector>

#include "objLoader/objLoader.h"

#include "Render/Render.h"
#include "Framebuffer/Framebuffer.h"
#include "DepthBuffer/Depthbuffer.h"
#include "Transform/Transform.h"
#include "Shader/Light.h"
#include "Shader/Material.h"
#include "Shadow/ShadowMap.h"

int main()
{
    const int width = 800;
    const int height = 800;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear(
        Vector3f(0.05f, 0.05f, 0.05f)
    );

    depthbuffer.clear();

    std::vector<Triangles> model =
        OBJLoader::load(
            "obj/african_head/african_head.obj"
        );

    std::cout << "Loaded triangles: "
              << model.size()
              << std::endl;

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

    Light light(
        Vector3f(3.0f, 4.0f, 3.0f),
        Vector3f(1.0f, 1.0f, 1.0f),
        1.0f,
        0.2f,
        32.0f
    );

    light.ambient_intensity = 0.1f;

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

    ShadowMap shadowMap(
        1024,
        1024
    );

    Mat4 lightView = lookAt(
        light.position,
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 0.0f)
    );

    Mat4 lightProjection = orthographic(
        -3.0f,
        3.0f,
        -3.0f,
        3.0f,
        0.1f,
        10.0f
    );

    Mat4 lightMVP =
        lightProjection *
        lightView *
        M;

    shadowMap.clear();

    for (Triangles& triangle : model)
    {
        shadowMap.renderTriangle(
            triangle,
            lightMVP
        );
    }

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
            material,
            shadowMap,
            lightMVP
        );
    }

    framebuffer.save(
        "african_head_shadow.ppm"
    );

    std::cout << "African head shadow render finished."
              << std::endl;

    return 0;
}