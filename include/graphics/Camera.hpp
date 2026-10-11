#pragma once

#include <array>

class Camera
{
public:
    void resize(unsigned width, unsigned height);

    const float* getView() const noexcept;
    const float* getProjection() const noexcept;

private:
    std::array<float, 16> view = {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, -3.f, 1.f
    };

    std::array<float, 16> projection{};
};