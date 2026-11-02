#include "graphics/Camera.hpp"

#include <cmath>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera(unsigned width, unsigned height, float fov, float nearPlane, float farPlane) : width{width}, height{height}, fov{fov}, nearPlane{nearPlane}, farPlane{farPlane}{
    if(height == 0 || width == 0)
        throw(std::runtime_error("Window size cannot be 0"));
    if(fov <= 0.0f || fov>= 180.0f)
        throw(std::runtime_error("Fov must be in range (0, 180)"));
    if(nearPlane<=0 || farPlane <= 0)
        throw(std::runtime_error("Projection planes cannot be non-positive"));
    if(nearPlane >= farPlane)
        throw(std::runtime_error("Near plane cannot be greater than far plane "));

    updateProjectionMatrix();
    
    
    cameraPosition= glm::vec3(0.0f, 0.0f, 3.0f); 
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 
    updateViewMatrix();
}

void Camera::resize(unsigned width, unsigned height)
{
    if (width == 0 || height == 0)
        throw(std::runtime_error("Window size cannot be 0"));
    this->width = width;
    this->height = height;
    updateProjectionMatrix();    
}

void Camera::setPosition(const glm::vec3& position){
    cameraPosition = position;
    updateViewMatrix();
}

void Camera::translatePosition(const glm::vec3& offset){
    cameraPosition += offset;
    updateViewMatrix();
}
void Camera::setDirection(const glm::vec3& direction){
    float lengthSquared = glm::dot(direction, direction);

    if (lengthSquared < 1e-12f)
        throw std::runtime_error("Direction must be non-zero");

    glm::vec3 newFront = glm::normalize(direction);

    glm::quat rotation = glm::rotation(cameraFront, newFront);

    cameraUp = glm::normalize(rotation * cameraUp);
    cameraFront = newFront;

    updateViewMatrix();
}
void Camera::lookAt(const glm::vec3& target){
    setDirection(target-cameraPosition);
}
void Camera::rotate(const glm::vec3& pivot, const glm::quat& rotation){
    float lengthSquared = glm::dot(rotation, rotation);

    if (!std::isfinite(lengthSquared) ||
        lengthSquared < 1e-12f)
        throw std::invalid_argument("Invalid rotation");

    glm::quat q = glm::normalize(rotation);

    cameraPosition = pivot + q * (cameraPosition - pivot);
    cameraFront = glm::normalize(q * cameraFront);
    cameraUp = glm::normalize(q * cameraUp);

    updateViewMatrix();
}
void Camera::setFov(float fov){
    if(fov <= 0.0f || fov>= 180.0f)
        throw(std::runtime_error("Fov must be in range (0, 180)"));
    
    this->fov = fov;
    updateProjectionMatrix();
}
void Camera::setNearPlane(float nearPlane){
    if(nearPlane<=0)
        throw(std::runtime_error("Projection planes cannot be non-positive"));
    if(nearPlane >= this->farPlane)
        throw(std::runtime_error("Near plane cannot be greater than far plane "));

    this->nearPlane = nearPlane;
    updateProjectionMatrix();
}
void Camera::setFarPlane(float farPlane){
    if(farPlane<=0)
        throw(std::runtime_error("Projection planes cannot be non-positive"));
    if(farPlane <= this->nearPlane)
        throw(std::runtime_error("Near plane cannot be greater than far plane "));
    this->farPlane = farPlane;
    updateProjectionMatrix();
}    
const glm::vec3& Camera::getPosition() const noexcept{
    return cameraPosition;
}
const glm::vec3& Camera::getCameraFront() const noexcept{
    return cameraFront;
}

const glm::mat4& Camera::getViewMatrix() const noexcept{
    return view;
}
const glm::mat4& Camera::getProjectionMatrix() const noexcept{
    return projection;
}

void Camera::updateViewMatrix(){
    view = glm::lookAt(
        cameraPosition,
        cameraPosition+cameraFront,
        cameraUp
    ); 
}

void Camera::updateProjectionMatrix(){
    projection = glm::perspective(
    glm::radians(fov),                  // FOV
    static_cast<float>(width) / height, // Aspect ratio
    nearPlane,                          // Near plane
    farPlane                            // Far plane
    );
}