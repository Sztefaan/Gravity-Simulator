#include "graphics/CameraController.hpp"
#include "graphics/Camera.hpp"

#include <algorithm>
#include <cmath>

CameraController::CameraController(Camera& cam, const glm::vec3& t, float d)
    : camera(cam), target(t), distance(d)
{
    update();
}

void CameraController::changeDistance(float factor)
{
    distance = std::clamp(distance * factor, 0.5f, 100.f);
    update();
}

void CameraController::changeAngle(float dAzimuth, float dElevation)
{
    constexpr float limit = glm::radians(89.f);
    azimuth  += dAzimuth;
    elevation = std::clamp(elevation + dElevation, -limit, limit);
    update();
}
void CameraController::moveTarget(const glm::vec3& dir, float dt){
    if (glm::dot(dir, dir) < 1e-6f)
        return;
    glm::vec3 forward(-cos(azimuth), 0.0f, -sin(azimuth));
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::vec3 d = glm::normalize(dir);
    glm::vec3 offset = right * d.x + up * d.y + forward * d.z;

    float speed = baseSpeed * distance;
    target += offset * (speed * dt);

    update();
}
void CameraController::update()
{
    glm::vec3 offset(
        distance * std::cos(elevation) * std::cos(azimuth),
        distance * std::sin(elevation),
        distance * std::cos(elevation) * std::sin(azimuth));

    camera.setPosition(target + offset);
    camera.lookAt(target);
}