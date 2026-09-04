#include "DepthBuffer/Depthbuffer.h"
#include <stdexcept>
#include <limits>

Depthbuffer::Depthbuffer(int width_, int height_) : width(width_), height(height_), depthbuffer(width_ * height_, 1.0f){}

void Depthbuffer::setDepthBuffer(const int x, const int y, const float depth)
{
    depthbuffer[getIndex(x, y)] = depth;
}

float Depthbuffer::getDepthBuffer(const int x, const int y) const 
{
    return depthbuffer[getIndex(x, y)];
}

int Depthbuffer::getIndex(int x, int y) const
{
    if(x < 0 || x >= width || y < 0 || y >= height){
        throw std::runtime_error("Depthbuffer coordinate out of range");
    }
    return y * width + x;
}

void Depthbuffer::clear(){
    std::fill(depthbuffer.begin(), depthbuffer.end(), 1.0f);
}