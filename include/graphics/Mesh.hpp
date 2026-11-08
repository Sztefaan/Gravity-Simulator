#pragma once

#include <vector>

struct Vertex
{
    float position[3];
    float normal[3];
    float u;
    float v;
};

class Mesh
{
public:
    enum class Primitive
    {
        Triangles,
        Lines
    };

    Mesh() = default;   
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    
    Mesh(Mesh&&) noexcept;
    Mesh& operator=(Mesh&&) noexcept;

    void init(const std::vector<Vertex>& vertices,
              Primitive primitive = Primitive::Triangles);
    void draw() const;
    void destroy();

private:
    unsigned int vao {0};
    unsigned int vbo {0};

    int vertexCount  {0};
    Primitive primitive = Primitive::Triangles;
};
