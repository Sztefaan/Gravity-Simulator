#include "physics/Simulation.hpp"
#include "physics/Integrator.hpp"

Simulation::Simulation() : m_integrator(std::make_unique<LeapfrogIntegrator>()){}

void Simulation::addBody(const Body& body)
{
    m_bodies.push_back(body);
    m_integrator->reset();   
}

void Simulation::clear()
{
    m_bodies.clear();
    m_integrator->reset();
}

void Simulation::step(double dt)
{
    m_integrator->step(m_bodies, m_gravity, dt);
}
