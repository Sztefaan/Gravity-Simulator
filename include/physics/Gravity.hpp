// simple newtonian gravity model (GMm/r^2, O(N^2)), later to be replaced with Barnes-Hut algorithm
#pragma once

#include <vector>
#include "Body.hpp"

class Gravity{
public:
    // Gravity(double G, double eps);
    void computeAcceleration(std::vector<Body>& bodies) const;
private:
    const double G = 6.674e-11;
    const double EPS = 1e-3;
};