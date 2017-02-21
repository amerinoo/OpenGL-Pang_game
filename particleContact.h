/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef particleContact_h
#define particleContact_h
#include "particle.h"
#include "vector3.h"

class ParticleContact {
public:
    ParticleContact(Particle *, Particle *, Vector3, double = 0);
private:
    Particle * particle1;
    Particle * particle2;
    Vector3 contactNormal;
    double interpenetration;
};
#endif // ifndef particleContact_h
