#include "Render/Render.h"
#include "Transform/Transform.h"
#include "Transform/Viewport.h"
#include "Transform/Clip.h"
#define EPSILON 0.0005

void render::RenderTriangles(Triangles& t, Framebuffer& framebuffer, Depthbuffer& depthbuffer, const Mat4 MVP, int width, int height){
    Triangles tri = t.toVec4T(t);
    Vector4f v0 = tri.getV0();
    Vector4f v1 = tri.getV1();
    Vector4f v2 = tri.getV2();
    v0 = MVP * v0;
    v1 = MVP * v1;
    v2 = MVP * v2;

    Triangles clipTri(v0, v1, v2);
    clipTri.setColors({t.color[0], t.color[1], t.color[2]});

    bool whetherInterpolate = false;
    std::vector<Triangles> clipList = Clip::toTriangleList(Clip::clipTriangle(clipTri, whetherInterpolate));
    Rasterizer rasterizer;
    for(auto& i : clipList){
        Vector3f vert0 = Viewport::transform(perspectiveDivide(i.getV0()),width, height);
        Vector3f vert1 = Viewport::transform(perspectiveDivide(i.getV1()), width, height);
        Vector3f vert2 = Viewport::transform(perspectiveDivide(i.getV2()), width, height);

        Triangles clippedTri = Triangles(vert0, vert1, vert2);
        clippedTri.setColors({i.color[0], i.color[1], i.color[2]});
        if(isFront(vert0, vert1, vert2)){
            rasterizer.drawTriangles(clippedTri, framebuffer, depthbuffer);
        }
    }
    

}

bool render::isFront(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2){
    Vector2f AB((v1 - v0).x, (v1 - v0).y);
    Vector2f AC((v2 - v0).x, (v2 - v0).y);
    float zPos = crossProduct(AB, AC);


    if(zPos > EPSILON){
        return true;
    }else if(zPos < -EPSILON){
        return false;
    }
    return false;
    
}