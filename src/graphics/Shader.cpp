#include "graphics/Shader.hpp"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file)
        throw std::runtime_error("Cannot open shader: " + path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::~Shader()
{
    destroy();
}

unsigned int Shader::compile(
    unsigned int type,
    const std::string& source)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        throw std::runtime_error("Failed to create shader");

    const char* code = source.c_str();

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[2048]{};

        glGetShaderInfoLog(
            shader,
            sizeof(log),
            nullptr,
            log
        );

        glDeleteShader(shader);

        throw std::runtime_error(
            std::string("Shader compilation error: ") + log
        );
    }

    return shader;
}

void Shader::load(
    const std::string& vertexPath,
    const std::string& fragmentPath)
{
    const auto vertexSource = readFile(vertexPath);
    const auto fragmentSource = readFile(fragmentPath);

    GLuint vertex = compile(GL_VERTEX_SHADER, vertexSource);
    GLuint fragment = 0;
    GLuint newProgram = 0;

    try
    {
        fragment = compile(GL_FRAGMENT_SHADER, fragmentSource);

        newProgram = glCreateProgram();

        if (newProgram == 0)
            throw std::runtime_error("Failed to create shader program");

        glAttachShader(newProgram, vertex);
        glAttachShader(newProgram, fragment);

        glLinkProgram(newProgram);

        GLint success = GL_FALSE;
        glGetProgramiv(newProgram, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[2048]{};

            glGetProgramInfoLog(
                newProgram,
                sizeof(log),
                nullptr,
                log
            );

            throw std::runtime_error(
                std::string("Shader linking error: ") + log
            );
        }
    }
    catch (...)
    {
        if (newProgram)
            glDeleteProgram(newProgram);

        if (fragment)
            glDeleteShader(fragment);

        glDeleteShader(vertex);
        throw;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    destroy();
    program = newProgram;
}

void Shader::use() const
{
    glUseProgram(program);
}

void Shader::setMat4(const char* name, const glm::mat4& matrix) const
{
    GLint location = glGetUniformLocation(program, name);

    if (location < 0)
        throw std::runtime_error(
            std::string("Uniform not found: ") + name
        );

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::setVec3(const char* name, const glm::vec3& value) const{
    GLint location = glGetUniformLocation(program, name);
    if(location<0)
        throw std::runtime_error("Uniform not found: "+std::string(name));
    glUniform3fv(location, 1, glm::value_ptr(value));
}
void Shader::destroy()
{
    if (program != 0)
    {
        glDeleteProgram(program);
        program = 0;
    }
}