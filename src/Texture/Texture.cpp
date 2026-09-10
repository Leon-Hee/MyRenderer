#include "Texture/Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture() : data(nullptr), width(0), height(0), channels(0){}

Texture::Texture(const std::string& path) : data(nullptr), width(0), height(0), channels(0) {
    data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        0
    );
    if (!data) {
    std::cerr << "Failed to load texture: " << path << std::endl;
    }
}

Vector3f Texture::sample(const Vector2f& uv) const{
    float u = std::clamp(uv.x, 0.0f, 1.0f);
    float v = std::clamp(uv.y, 0.0f, 1.0f);

    int x = static_cast<int> (u * (width - 1));
    int y = static_cast<int> ((1.0f - v) * (height - 1));

    int index = (y * width + x) * channels;

    float r = data[index] / 255.0f;
    float g = data[index + 1] / 255.0f;
    float b = data[index + 2] / 255.0f;
    return Vector3f(r, g, b);
}

Texture::~Texture(){
    if(data){
        stbi_image_free(data);
    }
}