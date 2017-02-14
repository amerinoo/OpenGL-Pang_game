/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef gravityForceGenerator_h
#define gravityForceGenerator_h
#include "forceGenerator.h"

class GravityForceGenerator : public ForceGenerator {
public:
    GravityForceGenerator();

    void setDirectionGravityForces(Vector3 v);
    void setGravityForces(double g);

    void updateForce(Particle * p);

protected:
    Vector3 directionGravityForces;
    double gravityForces;
};
#endif // ifndef gravityForceGenerator_h
