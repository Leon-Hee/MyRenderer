#pragma once 

class Color{
public:
    Color(float r_, float g_, float b_): m_r(r_), m_g(g_), m_b(b_){}
    Color(float a):m_r(a), m_g(a), m_b(a){}
    Color():m_r(0), m_g(0), m_b(0){}
    float r() const {return m_r;}
    float g() const {return m_g;}
    float b() const {return m_b;}
    Color operator+(const Color& color){
        Color result;
        result.m_r = m_r + color.m_r;
        result.m_g = m_g + color.m_g;
        result.m_b = m_b + color.m_b;
        return result;
    }
    Color operator-(const Color& color){
        Color result;
        result.m_r = m_r - color.m_r;
        result.m_g = m_g - color.m_g;
        result.m_b = m_b - color.m_b;
        return result; 
    }
    Color operator*(const Color& color){
        Color result;
        result.m_r = m_r * color.m_r;
        result.m_g = m_g * color.m_g;
        result.m_b = m_b * color.m_b;
        return result;
    }
    Color& operator+=(const Color& color){
        m_r += color.m_r;
        m_b += color.m_b;
        m_g += color.m_g;
        return *this;
    }
private:
    float m_r, m_g, m_b;

};