#include "graphics/Mesh.hpp"

#include <glad/gl.h>
#include <cstddef>
#include <stdexcept>

Mesh::~Mesh()
{
    destroy();
}
Mesh::Mesh(Mesh&& o) noexcept{
    vao = o.vao;
    vbo = o.vbo;
    vertexCount = o.vertexCount;
    primitive = o.primitive;
    o.vao = 0;
    o.vbo = 0;
    o.vertexCount = 0;
}
Mesh& Mesh::operator=(Mesh&& o) noexcept{
    if(this == &o){
        return *this;
    }
    vao = o.vao;
    vbo = o.vbo;
    vertexCount = o.vertexCount;
    primitive = o.primitive;
    o.vao = 0;
    o.vbo = 0;
    o.vertexCount = 0;
    return *this;
}


void Mesh::init(const std::vector<Vertex>& vertices, Primitive primitive)
{
    if (vertices.empty())
        throw std::runtime_error("Mesh has no vertices");

    destroy();

    vertexCount = static_cast<int>(vertices.size());
    this->primitive = primitive;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw() const
{
    glBindVertexArray(vao);

    const GLenum mode = primitive == Primitive::Lines ? GL_LINES : GL_TRIANGLES;
    glDrawArrays(mode, 0, vertexCount);

    glBindVertexArray(0);
}

void Mesh::destroy()
{
    if (vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (vao != 0)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    vertexCount = 0;
}
