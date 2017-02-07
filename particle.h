/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef particle_h
#define particle_h
#include "vector3.h"


class Particle {
public:
    Particle();
    Particle(double mass, Vector3 position, Vector3 velocity);

    double getMass();
    Vector3 getPosition();
    Vector3 getVelocity();

    void setMass(double mass);
    void setPosition(Vector3 position);
    void setVelocity(Vector3 velocity);

    void integrate(double time);

protected:
    double mass;
    Vector3 position;
    Vector3 velocity;
};
#endif // ifndef particle_h
