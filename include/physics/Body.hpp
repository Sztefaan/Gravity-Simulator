#pragma once
#include <glm/glm.hpp>

struct Body {
    glm::dvec3 position;
    glm::dvec3 velocity;
    glm::dvec3 acceleration{0.0};
    double mass;
    double radius;
};