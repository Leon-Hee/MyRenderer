#include "Rasterizer/Rasterizer.h"

int main() {
    const int width = 800;
    const int height = 600;

    Framebuffer framebuffer(width, height);
    Depthbuffer depthbuffer(width, height);

    framebuffer.clear(Vector3f(0.0f));
    depthbuffer.clear();

    // 远处的三角形
    Triangles farTriangle(
        Vector4f(150.0f, 150.0f, 0.8f, 1.0f),
        Vector4f(650.0f, 150.0f, 0.8f, 1.0f),
        Vector4f(400.0f, 500.0f, 0.8f, 1.0f)
    );

    farTriangle.color[0] = Vector3f(0.0f, 1.0f, 0.0f);
    farTriangle.color[1] = Vector3f(0.0f, 1.0f, 0.0f);
    farTriangle.color[2] = Vector3f(0.0f, 1.0f, 0.0f);

    // 近处的三角形
    Triangles nearTriangle(
        Vector4f(250.0f, 200.0f, 0.3f, 1.0f),
        Vector4f(700.0f, 200.0f, 0.3f, 1.0f),
        Vector4f(475.0f, 450.0f, 0.3f, 1.0f)
    );

    nearTriangle.color[0] = Vector3f(1.0f, 0.0f, 0.0f);
    nearTriangle.color[1] = Vector3f(1.0f, 0.0f, 0.0f);
    nearTriangle.color[2] = Vector3f(1.0f, 0.0f, 0.0f);

    Rasterizer rasterizer;

    // 故意先画远处，再画近处
    rasterizer.drawTriangles(
        farTriangle,
        framebuffer,
        depthbuffer
    );

    rasterizer.drawTriangles(
        nearTriangle,
        framebuffer,
        depthbuffer
    );

    framebuffer.save("output.ppm");

    return 0;
}