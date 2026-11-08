#pragma once
#include <glm/glm.hpp>

class Camera;

inline constexpr float BASE_RADIUS = 10.f;

class CameraController {
public:
    explicit CameraController(Camera& camera,
                              const glm::vec3& target = glm::vec3(0.f),
                              float distance = BASE_RADIUS);

    void changeDistance(float factor);
    void changeAngle(float dAzimuth, float dElevation); 
    void moveTarget(const glm::vec3& dir, float dt);
private:
    void update();

    Camera& camera;
    glm::vec3 target;
    float baseSpeed = 0.1f;
    float azimuth   = 0.f;
    float elevation = glm::radians(20.f);
    float distance;
};