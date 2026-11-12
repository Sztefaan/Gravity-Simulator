#pragma once 

#include <vector>
#include "Body.hpp"
#include "Gravity.hpp"
#include "Integrator.hpp"

class Simulation{
public:
    void addBody(const Body& body);
    void step(double dt);
    const std::vector<Body>& getBodies() const {return m_bodies; }
private:
    std::vector<Body> m_bodies;
    Gravity m_gravity;
    Integrator *m_integrator;
};