#include "Rasterizer/Rasterizer.h"
#include "Shader/Fragment.h"
#include "Shader/Shading.h"
#include "Transform/Transform.h"
#include <iostream>

static Vector3f interpolate(float alpha, float beta, float gamma, const Vector3f& vert1, const Vector3f& vert2, const Vector3f& vert3, float invW0, float invW1, float invW2){
    float denominator = alpha * invW0 + beta * invW1 + gamma * invW2;
    return (alpha * vert1 * invW0 + beta * vert2 * invW1 + gamma * vert3 * invW2) / denominator;
}

static float interpolate(float alpha, float beta, float gamma, float Var1, float Var2, float Var3, float invW0, float invW1, float invW2){
    float denominator = alpha * invW0 + beta * invW1 + gamma * invW2;
    return (alpha * invW0 * Var1 + beta * invW1 * Var2 + gamma * invW2 * Var3) / denominator;
}

static Vector2f interpolate(float alpha, float beta, float gamma, const Vector2f& uv0, const Vector2f& uv1, const Vector2f& uv2, float invW0, float invW1, float invW2){
    float denominator = alpha * invW0 + beta * invW1 + gamma * invW2;
    return (alpha * uv0 * invW0 + beta * uv1 * invW1 + gamma * uv2 * invW2) / denominator;
}

void Rasterizer::drawTriangles(const Triangles& triangles, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Light& light, const Vector3f& cameraPos, const Material& material, const ShadowMap& shadowMap, const Mat4& lightMVP) const {
    const Vector3f* vertices = triangles.getListVec3();
    int width = framebuffer.getWidth();
    int height = framebuffer.getHeight();
    float bbminx = std::min(vertices[0].x, std::min(vertices[1].x, vertices[2].x));
    float bbmaxx = std::max(vertices[0].x, std::max(vertices[1].x, vertices[2].x));
    float bbminy = std::min(vertices[0].y, std::min(vertices[1].y, vertices[2].y));
    float bbmaxy = std::max(vertices[0].y, std::max(vertices[1].y, vertices[2].y));

    int bbmin_x = std::max(0, static_cast<int>(std::floor(bbminx)));
    int bbmax_x = std::min(width - 1, static_cast<int>(std::ceil(bbmaxx)));
    int bbmin_y = std::max(0, static_cast<int>(std::floor(bbminy)));
    int bbmax_y = std::min(height - 1, static_cast<int>(std::ceil(bbmaxy)));

    for(int y = bbmin_y; y <= bbmax_y; y++){
        for(int x = bbmin_x; x <= bbmax_x; x++){
            float pixel_x = x + 0.5f;
            float pixel_y = y + 0.5f;
            if(!isInside(pixel_x, pixel_y, triangles)){
                continue;
            }
            auto[alpha, beta, gamma] = barycentric(pixel_x, pixel_y, triangles);
            float zp = interpolate(alpha, beta, gamma, vertices[0].z, vertices[1].z, vertices[2].z, triangles.invW[0], triangles.invW[1], triangles.invW[2]);
            
            float oldDepth = depthbuffer.getDepthBuffer(x, y);
            if (oldDepth > zp) {
                depthbuffer.setDepthBuffer(x, y, zp);
                Vector3f color_interpolate = interpolate(
                    alpha,
                    beta,
                    gamma,
                    triangles.color[0],
                    triangles.color[1],
                    triangles.color[2],
                    triangles.invW[0],
                    triangles.invW[1],
                    triangles.invW[2]
                );
                Vector3f normal_interpolate = interpolate(
                    alpha,
                    beta,
                    gamma,
                    triangles.normal[0],
                    triangles.normal[1],
                    triangles.normal[2],
                    triangles.invW[0],
                    triangles.invW[1],
                    triangles.invW[2]
                ).normalize();
                Vector3f position_interpolate = interpolate(
                    alpha,
                    beta,
                    gamma,
                    triangles.position[0],
                    triangles.position[1],
                    triangles.position[2],
                    triangles.invW[0],
                    triangles.invW[1],
                    triangles.invW[2]
                );
                Vector4f lightClip(
                    position_interpolate.x,
                    position_interpolate.y,
                    position_interpolate.z,
                    1.0f
                );

                lightClip = lightMVP * lightClip;

                Vector3f lightNDC = perspectiveDivide(lightClip);

                float shadowX = (lightNDC.x * 0.5f + 0.5f) * shadowMap.getWidth();
                float shadowY = (lightNDC.y * 0.5f + 0.5f) * shadowMap.getHeight();
                float shadowDepth = lightNDC.z * 0.5f + 0.5f;

                bool inShadow = false;

                if (shadowX >= 0.0f &&
                    shadowX < shadowMap.getWidth() &&
                    shadowY >= 0.0f &&
                    shadowY < shadowMap.getHeight() &&
                    shadowDepth >= 0.0f &&
                    shadowDepth <= 1.0f)
                {
                    int sx = static_cast<int>(shadowX);
                    int sy = static_cast<int>(shadowY);

                    float storedDepth = shadowMap.getDepth(sx, sy);

                    const float bias = 0.005f;

                    if (shadowDepth > storedDepth + bias)
                    {
                        inShadow = true;
                    }
                }
                
                Vector2f uv_interpolate = interpolate(
                    alpha,
                    beta,
                    gamma,
                    triangles.uv[0],
                    triangles.uv[1],
                    triangles.uv[2],
                    triangles.invW[0],
                    triangles.invW[1],
                    triangles.invW[2]
                );

                Vector3f textureColor;

                if (material.diffuseTexture != nullptr) {
                    textureColor = material.diffuseTexture->sample(uv_interpolate);
                } else {
                    textureColor = material.diffuseColor;
                }

                Fragment fragment(position_interpolate, normal_interpolate, textureColor, cameraPos, uv_interpolate);
                Shading shader;
                Vector3f ambient = shader.shade(
                    fragment,
                    light,
                    material,
                    Light::Type::Ambient
                );

                Vector3f diffuse;
                Vector3f specular;

                if (inShadow)
                {
                    diffuse = Vector3f(0.0f, 0.0f, 0.0f);
                    specular = Vector3f(0.0f, 0.0f, 0.0f);
                }
                else
                {
                    diffuse = shader.shade(
                        fragment,
                        light,
                        material,
                        Light::Type::Diffuse
                    );
                    specular = shader.shade(
                        fragment,
                        light,
                        material,
                        Light::Type::Specular
                    );
                }
                Vector3f end_color = ambient + diffuse + specular;
                framebuffer.setPixel(x, y, end_color);
            }
        }
    }
}

bool Rasterizer::isInside(const float x, const float y, const Triangles& triangles) const {
    Vector3f bary = barycentric(x, y, triangles);
    const float epsilon = 1e-6f;

    return bary.x >= -epsilon &&
        bary.y >= -epsilon &&
        bary.z >= -epsilon;
}

Vector3f Rasterizer::barycentric(float x, float y, const Triangles& triangles) const
{
    Vector3f v0 = triangles.vert0;
    Vector3f v1 = triangles.vert1;
    Vector3f v2 = triangles.vert2;

    Vector3f u = crossProduct(
        Vector3f(
            v2.x - v0.x,
            v1.x - v0.x,
            v0.x - x
        ),
        Vector3f(
            v2.y - v0.y,
            v1.y - v0.y,
            v0.y - y
        )
    );

    if (std::abs(u.z) < 1e-6f) {
        return Vector3f(-1.0f, 1.0f, 1.0f);
    }

    return Vector3f(
        1.0f - (u.x + u.y) / u.z,
        u.y / u.z,
        u.x / u.z
    );
}





