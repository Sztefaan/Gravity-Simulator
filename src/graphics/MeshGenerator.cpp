#include "graphics/MeshGenerator.hpp"
#include <cmath>
#include <vector>

Mesh MeshGenerator::generateSphere(float radius, unsigned int sectors, unsigned int stacks)
{
    std::vector<Vertex> grid;
    grid.reserve((stacks + 1) * (sectors + 1));

    for (unsigned int i = 0; i <= stacks; ++i)
    {
        float angle = M_PI / 2.0f - i * M_PI / stacks;
        float xy = radius * cosf(angle);
        float z  = radius * sinf(angle);

        for (unsigned int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = j * 2.0f * M_PI / sectors;

            Vertex vert;
            vert.position[0] = xy * cosf(sectorAngle);
            vert.position[1] = xy * sinf(sectorAngle);
            vert.position[2] = z;

            vert.normal[0] = vert.position[0] / radius;
            vert.normal[1] = vert.position[1] / radius;
            vert.normal[2] = vert.position[2] / radius;

            vert.u = (float)j / sectors;
            vert.v = (float)i / stacks;
            grid.push_back(vert);
        }
    }

    std::vector<Vertex> vertices;
    vertices.reserve(stacks * sectors * 6);

    for (unsigned int i = 0; i < stacks; ++i)
    {
        for (unsigned int j = 0; j < sectors; ++j)
        {
            unsigned int k1 = i * (sectors + 1) + j;
            unsigned int k2 = k1 + sectors + 1;

            if (i != 0)
            {
                vertices.push_back(grid[k1]);
                vertices.push_back(grid[k2]);
                vertices.push_back(grid[k1 + 1]);
            }
            if (i != stacks - 1) 
            {
                vertices.push_back(grid[k1 + 1]);
                vertices.push_back(grid[k2]);
                vertices.push_back(grid[k2 + 1]);
            }
        }
    }

    Mesh result;
    result.init(vertices, Mesh::Primitive::Triangles);
    return result;
}