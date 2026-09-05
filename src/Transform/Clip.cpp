#include "Transform/Clip.h"

bool Clip::inside(const Vector4f& v, ClipPlane clipPlane){
    switch (clipPlane)
    {
    case ClipPlane::Left:
        return v.x + v.w >= 0.0f;
    case ClipPlane::Right:
        return v.x - v.w <= 0.0f;
    case ClipPlane::Up:
        return v.y - v.w <= 0.0f;
    case ClipPlane::Down:
        return v.y + v.w >= 0.0f;
    case ClipPlane::Front:
        return v.z - v.w <= 0.0f;
    case ClipPlane::Back:
        return v.z + v.w >= 0.0f;
    
    default:
        return false;
    }
}

Vector4f Clip::intersect(const Vector4f& a, const Vector4f& b, ClipPlane clipPlane){
    float aValue;
    float bValue;
    float t;
    switch (clipPlane)
    {
    case ClipPlane::Left:
        aValue = a.x + a.w;
        bValue = b.x + b.w;
        break;
    case ClipPlane::Right:
        aValue = a.x - a.w;
        bValue = b.x - b.w;
        break;
    case ClipPlane::Up:
        aValue = a.y - a.w;
        bValue = b.y - b.w;
        break;
    case ClipPlane::Down:
        aValue = a.y + a.w;
        bValue = b.y + b.w;
        break;
    case ClipPlane::Front:
        aValue = a.z - a.w;
        bValue = b.z - b.w;
        break;
    case ClipPlane::Back:
        aValue = a.z + a.w;
        bValue = b.z + b.w;
        break;
    default:
        return Vector4f();
    
    }
    t = std::abs(aValue) / std::abs(aValue - bValue);
    return Vector4f(t * b + (1.0f - t) * a);
}

std::vector<Vector4f> Clip::clipSinglePlane (const std::vector<Vector4f>& polygon, ClipPlane clipPlane){
    std::vector<Vector4f> output;
    if(polygon.empty()){
        return output;
    }
    Vector4f previous = polygon.back();
    bool previousInside = inside(previous, clipPlane);
    for(const auto& current : polygon){
        bool currentInside = inside(current, clipPlane);
        if(previousInside && currentInside){
            output.push_back(current);
        }else if(previousInside && !currentInside){
            Vector4f point = intersect(previous, current, clipPlane);
            output.push_back(point);
        }else if(!previousInside && currentInside){
            Vector4f point = intersect(current, previous, clipPlane);
            output.push_back(point);
            output.push_back(current);
        }
        previous = current;
        previousInside = currentInside;
    }
    return output;
}

std::vector<Vector4f> Clip::clipTriangle(const Triangles& t){
    std::vector<Vector4f> output = {
        t.getV0(),
        t.getV1(),
        t.getV2()
    };

    output = clipSinglePlane(output, ClipPlane::Left);
    output = clipSinglePlane(output, ClipPlane::Right);
    output = clipSinglePlane(output, ClipPlane::Up);
    output = clipSinglePlane(output, ClipPlane::Down);
    output = clipSinglePlane(output, ClipPlane::Front);
    output = clipSinglePlane(output, ClipPlane::Back);

    return output;
    
    
}

std::vector<Triangles> Clip::toTriangleList(const std::vector<Vector4f> polyon){
    std::vector<Triangles> output;
    if(polyon.size() < 3){
        return output;
    }
    for(int i = 1; i < polyon.size() - 1; i ++){
        output.push_back(Triangles(polyon[0], polyon[i], polyon[i + 1]));
    }
    return output;
}