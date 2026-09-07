#include "Rasterizer/Rasterizer.h"
#include <iostream>

static Vector3f interpolate(float alpha, float beta, float gamma, const Vector3f& vert1, const Vector3f& vert2, const Vector3f& vert3, float weight){
    return (alpha * vert1 + beta * vert2 + gamma * vert3) / weight;
}

void Rasterizer::drawTriangles(const Triangles& triangles, Framebuffer& framebuffer, Depthbuffer& depthbuffer) const {
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

            float zp = alpha * vertices[0].z + beta * vertices[1].z + gamma * vertices[2].z;
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
                    1
                );
                framebuffer.setPixel(x, y, color_interpolate);
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





