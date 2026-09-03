#include "Framebuffer.h"
#include <fstream>
#include <cstdint>
#include <stdexcept>

Framebuffer::Framebuffer(int width_, int height_) : width(width_), height(height_), pixel(width_ * height_){
}

int Framebuffer::getWidth() const{
    return width;
}

int Framebuffer::getHeight() const{
    return height;
}

void Framebuffer::setPixel(int x, int y, const Color& color){
    if(x >= width || x < 0 || y >= height || y < 0){
        return;
    }
    pixel[y * width + x] = color;
}

Color Framebuffer::getPixel(int x, int y){
    if(x >= width || x < 0 || y >= height || y < 0){
        throw std::out_of_range("Framebuffer coordinate out of range");
    }
    return pixel[y * width + x];
}

void Framebuffer::clear(const Color& color){
    for(Color& c : pixel){
        c = color;
    }
}

void Framebuffer::save(const std::string& path){
    std::ofstream file(path, std::ios::binary);
    if(!file){
        throw std::runtime_error("Failed to open the file: " + path);
    }

    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for(int y = height - 1; y >= 0; y--){
        for(int x = 0; x < width; x++){
            const Color& color = pixel[y * width + x];
            uint8_t r = static_cast<uint8_t>(color.r());
            uint8_t g = static_cast<uint8_t>(color.g());
            uint8_t b = static_cast<uint8_t>(color.b());
            file.write(reinterpret_cast<const char*>(&r), 1);//reinterpret_cast<const char*>只是把这个地址当成 const char* 来看，没有改变地址
            file.write(reinterpret_cast<const char*>(&g), 1);
            file.write(reinterpret_cast<const char*>(&b), 1);
        }
    }
    if(!file){
        throw std::runtime_error("Failed to write the file :" + path);
    }
}