#include "physics/Integrator.hpp"

#include "physics/Integrator.hpp"

void LeapfrogIntegrator::step(std::vector<Body>& bodies, const Gravity& gravity, double dt)
{
    if (m_reset) {
        gravity.computeAcceleration(bodies);
        m_reset = false;
    }


    for (Body& b : bodies) {
        b.velocity += 0.5 * dt * b.acceleration;
        b.position += dt * b.velocity;
    }

    gravity.computeAcceleration(bodies);

    for (Body& b : bodies)
        b.velocity += 0.5 * dt * b.acceleration;
}