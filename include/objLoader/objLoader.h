#pragma once

#include <string>
#include <vector>

#include "Triangle/Triangles.h"

class OBJLoader
{
public:
    static std::vector<Triangles> load(const std::string& path);
};