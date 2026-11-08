#include "graphics/CameraController.hpp"
#include "graphics/Camera.hpp"

#include <algorithm>
#include <cmath>

CameraController::CameraController(Camera& cam, const glm::vec3& t, float d)
    : camera(cam), target(t), distance(d)
{
    update();
}

void CameraController::changeDistance(float dr)
{
    distance = std::clamp(distance + dr, 0.5f, 100.f);
    update();
}

void CameraController::changeAngle(float dAzimuth, float dElevation)
{
    constexpr float limit = glm::radians(89.f);
    azimuth  += dAzimuth;
    elevation = std::clamp(elevation + dElevation, -limit, limit);
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