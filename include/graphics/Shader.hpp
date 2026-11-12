#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

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
    void setMat4(const char* name, const glm::mat4& matrix) const;
    void setVec3(const char* name, const glm::vec3& value) const;

    void destroy();

private:
    unsigned int program = 0;
    static std::string readFile(const std::string& path);
    static unsigned int compile(unsigned int type, const std::string& source);
};