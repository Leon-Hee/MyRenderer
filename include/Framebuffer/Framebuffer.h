#pragma once 

#include <vector>
#include "Color.hpp"

class Framebuffer{
public:
    Framebuffer(int width, int height);
    int getWidth() const ;
    int getHeight() const ;
    void setPixel(int x, int y, const Color& color);
    Color getPixel(int x, int y);

    void clear(const Color& color);
    void save(const std::string& path);
private:
    int width, height;
    std::vector<Color> pixel;
};