#include "physics/Gravity.hpp"
#include <glm/glm.hpp>

void Gravity::computeAcceleration(std::vector<Body>& bodies) const{
    for(Body& b : bodies){
        b.acceleration = glm::dvec3(0.0);
    }

    for(int i=0; i<bodies.size(); ++i){
        for(int j = i+1 ; j<bodies.size(); ++j ){
            const glm::dvec3 dis = bodies[j].position - bodies[i].position;
            const double r2 = glm::dot(dis,dis)+EPS;
            const double invR3 = 1.0 / (r2 * std::sqrt(r2));

            bodies[i].acceleration += G * bodies[j].mass * invR3 * dis;
            bodies[j].acceleration -= G * bodies[i].mass * invR3 * dis;            
        }
    }
}