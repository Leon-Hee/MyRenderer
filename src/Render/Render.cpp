#include "Render/Render.h"
#include "Transform/Transform.h"
#include "Transform/Viewport.h"
#include "Transform/Clip.h"

void render::RenderTriangles(Triangles& t, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Mat4 MVP, int width, int height){
    Triangles tri = t.toVec4T(t);
    Vector4f v0 = tri.getV0();
    Vector4f v1 = tri.getV1();
    Vector4f v2 = tri.getV2();
    v0 = MVP * v0;
    v1 = MVP * v1;
    v2 = MVP * v2;

    Triangles clipTri(v0, v1, v2);
    std::vector<Triangles> clipList = Clip::toTriangleList(Clip::clipTriangle(clipTri));
    std::vector<Triangles> renderList ;
    Rasterizer rasterizer;
    for(const auto& i : clipList){

        Vector3f vert0 = Viewport::transform(perspectiveDivide(i.getV0()),width, height);
        Vector3f vert1 = Viewport::transform(perspectiveDivide(i.getV1()), width, height);
        Vector3f vert2 = Viewport::transform(perspectiveDivide(i.getV2()), width, height);

        Triangles clippedTri = Triangles(vert0, vert1, vert2);
        rasterizer.drawTriangles(clippedTri, framebuffer, depthbuffer);
    }

    

}