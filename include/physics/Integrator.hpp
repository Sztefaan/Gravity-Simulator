#pragma once 
#include <vector>
#include "Body.hpp"
#include "Gravity.hpp"

class Integrator{
public:
    virtual ~Integrator() = default;
    virtual void step(std::vector<Body>& bodies,
                      const Gravity& gravity, double dt) = 0;
    virtual void reset() = 0; 
};

class LeapfrogIntegrator : public Integrator{
public:
    virtual void step(std::vector<Body>& bodies,
                      const Gravity& gravity, double dt);
    virtual void reset() { m_reset = true; }
private:
    bool m_reset = true;
};
