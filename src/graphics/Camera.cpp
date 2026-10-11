#include "graphics/Camera.hpp"

#include <cmath>

void Camera::resize(unsigned width, unsigned height)
{
    if (width == 0 || height == 0)
        return;

    constexpr float pi = 3.14159265358979323846f;
    constexpr float fov = 60.0f;
    constexpr float nearPlane = 0.1f;
    constexpr float farPlane = 100.0f;

    const float aspect =
        static_cast<float>(width) / static_cast<float>(height);

    const float fovRadians = fov * pi / 180.0f;
    const float f = 1.0f / std::tan(fovRadians / 2.0f);

    projection = {
        f / aspect, 0.f, 0.f, 0.f,
        0.f, f, 0.f, 0.f,
        0.f, 0.f,
        (farPlane + nearPlane) / (nearPlane - farPlane), -1.f,
        0.f, 0.f,
        (2.f * farPlane * nearPlane) / (nearPlane - farPlane), 0.f
    };
}

const float* Camera::getView() const noexcept
{
    return view.data();
}

const float* Camera::getProjection() const noexcept
{
    return projection.data();
}