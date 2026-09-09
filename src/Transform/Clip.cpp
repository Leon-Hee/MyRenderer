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

Vertex Clip::intersect(const Vertex& _a, const Vertex& _b, ClipPlane clipPlane){
    float aValue;
    float bValue;
    float t;
    const Vector4f a = _a.position;
    const Vector4f b = _b.position;
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
        return Vertex();
    
    }
    t = std::abs(aValue) / std::abs(aValue - bValue);
    Vertex result;

    result.position = _a.position * (1.0f - t) + t * _b.position;
    result.color = _a.color * (1.0f - t) + t * _b.color;
    result.normal = _a.normal * (1.0f - t) + t * _b.normal;
    result.worldPos = _a.worldPos * (1.0f - t) + t * _b.worldPos;
    return result;
}

std::vector<Vertex> Clip::clipSinglePlane (const std::vector<Vertex>& polygon, ClipPlane clipPlane){
    std::vector<Vertex> output;
    if(polygon.empty()){
        return output;
    }
    Vertex previous = polygon.back();
    bool previousInside = inside(previous.position, clipPlane);
    for(const auto& current : polygon){
        bool currentInside = inside(current.position, clipPlane);
        if(previousInside && currentInside){
            output.push_back(current);
        }else if(previousInside && !currentInside){
            Vertex point = intersect(previous, current, clipPlane);
            output.push_back(point);
        }else if(!previousInside && currentInside){
            Vertex point = intersect(current, previous, clipPlane);
            output.push_back(point);
            output.push_back(current);
        }
        previous = current;
        previousInside = currentInside;
    }
    return output;
}

std::vector<Vertex> Clip::clipTriangle(const Triangles& t, bool whetherInterpolate = true){
    std::vector<Vertex> output = {
        Vertex(t.getV0(), t.color[0], t.normal[0], t.position[0]),
        Vertex(t.getV1(), t.color[1], t.normal[1], t.position[1]),
        Vertex(t.getV2(), t.color[2], t.normal[2], t.position[2])
    };

    output = clipSinglePlane(output, ClipPlane::Left);
    output = clipSinglePlane(output, ClipPlane::Right);
    output = clipSinglePlane(output, ClipPlane::Up);
    output = clipSinglePlane(output, ClipPlane::Down);
    output = clipSinglePlane(output, ClipPlane::Front);
    output = clipSinglePlane(output, ClipPlane::Back);

    if(!whetherInterpolate && !output.empty()){
        Vector3f flatColor = t.color[0];
        for(auto& vertex : output){
            vertex.color = flatColor;
        }
    }

    return output;
    
    
}

std::vector<Triangles> Clip::toTriangleList(const std::vector<Vertex> polyon){
    std::vector<Triangles> output;
    if(polyon.size() < 3){
        return output;
    }
    for(int i = 1; i < polyon.size() - 1; i ++){
        Triangles t(polyon[0].position, polyon[i].position, polyon[i + 1].position);
        t.color[0] = polyon[0].color;
        t.color[1] = polyon[i].color;
        t.color[2] = polyon[i + 1].color;
        t.normal[0] = polyon[0].normal;
        t.normal[1] = polyon[i].normal;
        t.normal[2] = polyon[i + 1].normal;
        t.position[0] = polyon[0].worldPos;
        t.position[1] = polyon[i].worldPos;
        t.position[2] = polyon[i + 1].worldPos;
        output.push_back(t);
    }
    return output;
}

