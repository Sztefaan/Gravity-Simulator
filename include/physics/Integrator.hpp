#pragma once 
#include <vector>
#include "Body.hpp"
#include "Gravity.hpp"

class Integrator{
public:
    virtual ~Integrator() = default;
    virtual void step(std::vector<Body>& bodies,
                      const Gravity& gravity, double dt) = 0;
};

class LeapfrogIntegrator{
public:
    virtual void step(std::vector<Body>& bodies,
                      const Gravity& gravity, double dt);
private:
        
};
