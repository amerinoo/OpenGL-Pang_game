/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ballPlaneColDetect_h
#define ballPlaneColDetect_h
#include "ball.h"
#include "plane.h"
#include "particleContact.h"

class BallPlaneColDetect {
public:
    BallPlaneColDetect();
    ParticleContact * getParticleContact(Ball * ball, Plane plane);
    ParticleContact * getParticleContact(Ball * ball, Plane plane, double d);
};
#endif // ifndef ballPlaneColDetect_h
