#include "Transform/Transform.h"

#define MY_PI 3.141592653f

Mat4 translate(float x, float y, float z){
    Mat4 result = Mat4::Identity();
    result[0][3] = x;
    result[1][3] = y;
    result[2][3] = z;
    return result;
}

Mat4 scale(float x, float y, float z){
    Mat4 result = Mat4::Identity();
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    return result;
}

Mat4 scale(float arg){
    Mat4 result = Mat4::Identity();
    for(int i = 0; i <= 2; i++){
        result[i][i] = arg;
    }
    return result;
}

Mat4 rotate(Axis axis, float angle){
    float radians = angle * MY_PI / 180.0f;
    Mat4 result = Mat4::Identity();
    if(axis == X){
        result[1][1] = std::cos(radians);
        result[1][2] = -std::sin(radians);
        result[2][1] = std::sin(radians);
        result[2][2] = std::cos(radians);
        return result;
    }else if(axis == Y){
        result[0][0] = std::cos(radians);
        result[0][2] = std::sin(radians);
        result[2][0] = -std::sin(radians);
        result[2][2] = std::cos(radians);
        return result;
    }else if(axis == Z){
        result[0][0] = std::cos(radians);
        result[0][1] = -std::sin(radians);
        result[1][0] = std::sin(radians);
        result[1][1] = std::cos(radians);
        return result;
    }else{
        throw std::runtime_error("Please add correct axis!");
    }
}

Mat4 lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up){
    Vector3f sight = (center - eye).normalize();
    Vector3f xAxis = crossProduct(sight, up).normalize();
    Vector3f yAxis = crossProduct(xAxis, sight).normalize();
    Mat4 result = Mat4::Identity();
    
    result[0][0] = xAxis.x;
    result[0][1] = xAxis.y;
    result[0][2] = xAxis.z;
    
    result[1][0] = yAxis.x;
    result[1][1] = yAxis.y;
    result[1][2] = yAxis.z;

    result[2][0] = -sight.x;
    result[2][1] = -sight.y;
    result[2][2] = -sight.z;

    result[0][3] = -dotProduct(xAxis, eye);
    result[1][3] = -dotProduct(yAxis, eye);
    result[2][3] = dotProduct(sight, eye);

    return result;
}

Mat4 perspective(float fov, float aspect, float zNear, float zFar){
    float radians = fov * MY_PI / 180.0f;
    Mat4 result = Mat4::Identity();
    float tanYd2 = std::tan(radians / 2.0f);
    result[0][0] = 1.0f / (aspect * tanYd2);
    result[1][1] = 1.0f / tanYd2;
    result[2][2] = (zFar + zNear) / (zNear - zFar);
    result[2][3] = 2 * zFar * zNear / (zNear - zFar);
    result[3][2] = -1.0f;
    return result;
}

Mat4 getMVP(const Mat4& model, const Mat4& view, const Mat4& projection)
{
    return projection * view * model;
}

Vector3f perspectiveDivide(const Vector4f& clip){
    return Vector3f(clip.x / clip.w, clip.y / clip.w, clip.z / clip.w);
}