/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "gravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator() : ForceGenerator(),
    directionGravityForces(Vector3(0, -1, 0)), gravityForces(9.8){ }

void GravityForceGenerator::setDirectionGravityForces(Vector3 v){ directionGravityForces = v; }

void GravityForceGenerator::setGravityForces(double g){ gravityForces = g; }

void GravityForceGenerator::updateForce(Particle * p){
    Vector3 force = directionGravityForces * gravityForces * p->getMass();

    p->addForce(force);
}
