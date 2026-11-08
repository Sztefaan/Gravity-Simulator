#pragma once
#include "graphics/Mesh.hpp"

class MeshGenerator{
public:
    static Mesh generateSphere(float radius, unsigned int sectors, unsigned int stacks);
};