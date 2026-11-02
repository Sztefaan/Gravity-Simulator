#pragma once

#include <glm/glm.hpp>
class Camera
{
public:
    Camera(unsigned width, unsigned height, float fov = 45.0f, float nearPlane = 0.1f, float farPlane=100.0f);
    
    void setPosition(const glm::vec3& position);
    void translatePosition(const glm::vec3& offset);
    void setDirection(const glm::vec3& direction);
    void rotate(const glm::vec3& pivot, const glm::quat& rotation);
    void lookAt(const glm::vec3& target);

    void resize(unsigned width, unsigned height);
    void setFov(float fov);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    
    const glm::vec3& getPosition() const noexcept;
    const glm::vec3& getCameraFront() const noexcept;

    const glm::mat4& getViewMatrix() const noexcept;
    const glm::mat4& getProjectionMatrix() const noexcept;

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    
    unsigned width, height;
    float nearPlane, farPlane;    
    float fov;
    glm::mat4 projection;
    
    glm::vec3 cameraPosition; 
    glm::vec3 cameraFront;
    glm::vec3 cameraUp; 
    glm::mat4 view;
};