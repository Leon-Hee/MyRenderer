#pragma once
#include <vector>

class Depthbuffer{
public:
    Depthbuffer(int width_, int height_);
    void setDepthBuffer(const int x, const int y, const float depth);
    float getDepthBuffer(const int x, const int y) const ;
    int getIndex(int x, int y) const;
    void clear();
private:
    int width, height;
    std::vector<float>depthbuffer;
};