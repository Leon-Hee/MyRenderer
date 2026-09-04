#include "Math/Vector.hpp"
#include <iostream>




Vector2f::Vector2f() : x(0), y(0)
{
    
}

Vector2f::Vector2f(float num) : x(num), y(num)
{
    
}

Vector2f::Vector2f(float xx, float yy): x(xx), y(yy)
{
    
}

Vector2f Vector2f::operator-(const Vector2f& v) const
{
    return Vector2f(x - v.x, y - v.y);
}

Vector2f Vector2f::operator-() const
{
    return Vector2f(-x, -y);
}

Vector2f Vector2f::operator/(const float& a) const
{
    return Vector2f(x / a, y /a);
}

Vector2f operator*(const float& a, const Vector2f& v)
{
    return Vector2f(v.x * a, v.y * a);
}

std::ostream& operator <<(std::ostream& os, const Vector2f& v)
{
    return os << v.x << ", " << v.y ;
}

Vector2f Vector2f::operator*(const float& a) const
{
    return Vector2f(x * a, y * a);
}

Vector2f& Vector2f::operator+=(const Vector2f& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& v) const
{
    return Vector2f(x + v.x, y + v.y);
}
