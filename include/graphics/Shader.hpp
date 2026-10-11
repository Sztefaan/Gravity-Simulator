#pragma once

#include <string>

class Shader
{
public:
    Shader() = default;
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void load(const std::string& vertexPath,
              const std::string& fragmentPath);

    void use() const;
    void setMat4(const char* name, const float* matrix) const;

    void destroy();

private:
    unsigned int program = 0;

    static unsigned int compile(
        unsigned int type,
        const std::string& source
    );
};