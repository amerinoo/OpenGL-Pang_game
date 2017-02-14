/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef forceGenerator_h
#define forceGenerator_h
#include "particle.h"

class ForceGenerator {
public:
    ForceGenerator();

    virtual void updateForce(Particle * p) = 0;
};
#endif
