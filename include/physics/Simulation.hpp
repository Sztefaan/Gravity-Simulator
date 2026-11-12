#pragma once 
#include <memory> 

#include "Body.hpp"
#include "Gravity.hpp"
#include "Integrator.hpp"
class Simulation{
public:
    Simulation();
    
    void addBody(const Body& body);
    void clear();
    void step(double dt);
    const std::vector<Body>& getBodies() const {return m_bodies; }
private:
    std::vector<Body> m_bodies;
    Gravity m_gravity;
    std::unique_ptr<Integrator>  m_integrator;
};