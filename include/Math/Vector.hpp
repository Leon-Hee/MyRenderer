#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>


class Vector2f{ 
public:
    float x, y;
    float norm() const;
    Vector2f();
    Vector2f(float num);
    Vector2f(float xx, float yy);
    Vector2f operator+(const Vector2f& v) const;
    Vector2f operator-(const Vector2f& v) const;
    Vector2f& operator+=(const Vector2f& v);
    Vector2f operator-() const;
    Vector2f operator*(const float& a) const;
    Vector2f operator/(const float& a) const;
    friend std::ostream& operator <<(std::ostream& os, const Vector2f& v);
    friend Vector2f operator*(const float& a, const Vector2f& v);
    float operator[](int index) const;
    float& operator[](int index);
};

inline float Vector2f::operator[](int index) const {
    return (&x)[index];
}

inline float& Vector2f::operator[](int index){
    return (&x)[index];
}

class Vector3f{
public:
    float x, y, z;
    float norm() const{return std::sqrt(x * x + y * y + z * z);};
    Vector3f() : x(0), y(0), z(0){}
    Vector3f(float num) : x(num), y(num), z(num){}
    Vector3f(float xx, float yy, float zz) : x(xx), y(yy), z(zz){}
    Vector3f operator+(const Vector3f& v) const {return Vector3f(x + v.x, y + v.y, z + v.z);};
    Vector3f operator-(const Vector3f& v) const {return Vector3f(x - v.x, y - v.y, z - v.z);};
    Vector3f operator-() const {return Vector3f(-x, -y, -z);};
    Vector3f operator*(const float a) const {return Vector3f(x * a, y * a, z * a);};
    friend Vector3f operator*(const float a, const Vector3f& v) {return Vector3f(a * v.x, a * v.y, a * v.z);};
    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v){return os << v.x << ", " << v.y << ", " << v.z;};
    float operator[](int index) const;
    float& operator[](int index);
    Vector3f operator/(const float a) const {return Vector3f(x / a, y / a, z / a);};
    Vector3f& operator+=(const Vector3f& v){x += v.x; y += v.y; z += v.z; return *this;};
    Vector3f normalized() const;
    Vector3f& normalize();
};
class Vector4f {
public:
    float x, y, z, w;

    Vector4f() : x(0), y(0), z(0), w(0) {}
    Vector4f(float num) : x(num), y(num), z(num), w(num) {}
    Vector4f(float xx, float yy, float zz, float ww)
        : x(xx), y(yy), z(zz), w(ww) {}

    float norm() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4f operator+(const Vector4f& v) const {
        return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vector4f operator-(const Vector4f& v) const {
        return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vector4f operator-() const {
        return Vector4f(-x, -y, -z, -w);
    }

    Vector4f operator*(float a) const {
        return Vector4f(x * a, y * a, z * a, w * a);
    }

    Vector4f operator/(float a) const {
        return Vector4f(x / a, y / a, z / a, w / a);
    }

    Vector4f& operator+=(const Vector4f& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    float operator[](int index) const {
        return (&x)[index];
    }

    float& operator[](int index) {
        return (&x)[index];
    }

    friend Vector4f operator*(float a, const Vector4f& v) {
        return Vector4f(a * v.x, a * v.y, a * v.z, a * v.w);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector4f& v) {
        return os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
    }
};

inline float Vector3f::operator[](int index) const{
    return (&x)[index];
}

inline float& Vector3f::operator[](int index){
    return (&x)[index];
}

inline Vector3f lerp(const Vector3f& v1, const Vector3f& v2, const float t){
    return Vector3f(v1 * (1 - t) + v2 * t);
}

inline float dotProduct(const Vector2f& v1, const Vector2f& v2){
    return v1.x * v2.x + v1.y * v2.y;
}

inline float dotProduct(const Vector3f& v1, const Vector3f& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3f crossProduct(const Vector3f &a, const Vector3f &b)
{
    return Vector3f(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
    );
}

inline Vector4f toVec4(const Vector3f& v) {
    return Vector4f(v.x, v.y, v.z, 1.0f);
}

inline Vector3f Vector3f::normalized() const{
    float length = norm();
    if(length == 0){
        return Vector3f();
    }
    return *this / length;
}

inline Vector3f& Vector3f::normalize(){
    float length = norm();
    if(length == 0){
        return *this;
    }
    x /= length;
    y /= length;
    z /= length;

    return *this;
}