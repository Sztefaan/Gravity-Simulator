#pragma once
#include <glm/glm.hpp>

class Camera;

inline constexpr float BASE_RADIUS = 10.f;

class CameraController {
public:
    explicit CameraController(Camera& camera,
                              const glm::vec3& target = glm::vec3(0.f),
                              float distance = BASE_RADIUS);

    void changeDistance(float dr);
    void changeAngle(float dAzimuth, float dElevation); 

private:
    void update();

    Camera& camera;
    glm::vec3 target;
    float azimuth   = 0.f;
    float elevation = glm::radians(20.f);
    float distance;
};