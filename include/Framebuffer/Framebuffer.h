#pragma once 

#include <vector>
#include "Math/Vector.hpp"

class Framebuffer{
public:
    Framebuffer(int width, int height);
    int getWidth() const ;
    int getHeight() const ;
    void setPixel(int x, int y, const Vector3f& color);
    Vector3f getPixel(int x, int y);

    void clear(const Vector3f& color);
    void clear();
    void save(const std::string& path);
private:
    int width, height;
    std::vector<Vector3f> pixel;
};