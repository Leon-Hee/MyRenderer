#include "objLoader/objLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>


struct OBJIndex
{
    int position;
    int uv;
    int normal;
};


static OBJIndex parseFaceVertex(const std::string& vertex)
{
    OBJIndex index{-1, -1, -1};

    std::stringstream ss(vertex);
    std::string value;

    // position
    if (std::getline(ss, value, '/'))
    {
        index.position = std::stoi(value) - 1;
    }

    // uv
    if (std::getline(ss, value, '/'))
    {
        if (!value.empty())
            index.uv = std::stoi(value) - 1;
    }

    // normal
    if (std::getline(ss, value, '/'))
    {
        if (!value.empty())
            index.normal = std::stoi(value) - 1;
    }

    return index;
}


std::vector<Triangles> OBJLoader::load(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open OBJ: "
                  << path
                  << std::endl;

        return {};
    }

    std::vector<Vector3f> positions;
    std::vector<Vector2f> uvs;
    std::vector<Vector3f> normals;

    std::vector<Triangles> triangles;

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string type;
        ss >> type;


        // =========================
        // Vertex
        // =========================

        if (type == "v")
        {
            float x, y, z;

            ss >> x >> y >> z;

            positions.emplace_back(x, y, z);
        }


        // =========================
        // Texture Coordinate
        // =========================

        else if (type == "vt")
        {
            float u, v;

            ss >> u >> v;

            uvs.emplace_back(u, v);
        }


        // =========================
        // Normal
        // =========================

        else if (type == "vn")
        {
            float x, y, z;

            ss >> x >> y >> z;

            normals.emplace_back(x, y, z);
        }


        // =========================
        // Face
        // =========================

        else if (type == "f")
        {
            std::string a, b, c;

            ss >> a >> b >> c;

            OBJIndex i0 = parseFaceVertex(a);
            OBJIndex i1 = parseFaceVertex(b);
            OBJIndex i2 = parseFaceVertex(c);


            // =========================
            // Position
            // =========================

            Vector4f p0(
                positions[i0.position].x,
                positions[i0.position].y,
                positions[i0.position].z,
                1.0f
            );

            Vector4f p1(
                positions[i1.position].x,
                positions[i1.position].y,
                positions[i1.position].z,
                1.0f
            );

            Vector4f p2(
                positions[i2.position].x,
                positions[i2.position].y,
                positions[i2.position].z,
                1.0f
            );


            Triangles triangle(
                p0,
                p1,
                p2
            );


            // =========================
            // Normal
            // =========================

            if (!normals.empty() &&
                i0.normal >= 0 &&
                i1.normal >= 0 &&
                i2.normal >= 0)
            {
                triangle.setNormal(
                    normals[i0.normal],
                    normals[i1.normal],
                    normals[i2.normal]
                );
            }


            // =========================
            // UV
            // =========================

            if (!uvs.empty() &&
                i0.uv >= 0 &&
                i1.uv >= 0 &&
                i2.uv >= 0)
            {
                triangle.setUV(
                    uvs[i0.uv],
                    uvs[i1.uv],
                    uvs[i2.uv]
                );
            }


            // =========================
            // Color
            // =========================

            triangle.setColors({
                Vector3f(1.0f, 1.0f, 1.0f),
                Vector3f(1.0f, 1.0f, 1.0f),
                Vector3f(1.0f, 1.0f, 1.0f)
            });


            triangles.push_back(triangle);
        }
    }

    file.close();

    std::cout << "OBJ loaded: "
              << triangles.size()
              << " triangles"
              << std::endl;

    return triangles;
}