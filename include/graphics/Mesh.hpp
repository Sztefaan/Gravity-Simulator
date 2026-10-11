#pragma once

#include <vector>

struct Vertex
{
    float position[3];
    float color[3];
};

class Mesh
{
public:
    Mesh() = default;
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void init(const std::vector<Vertex>& vertices);
    void draw() const;
    void destroy();

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;

    int vertexCount = 0;
};