/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ballBallColDetect_h
#define ballBallColDetect_h
#include "ball.h"
#include "plane.h"
#include "particleContact.h"

class BallBallColDetect {
public:
    BallBallColDetect();
    ParticleContact * getParticleContact(Ball * ball1, Ball * ball2);
};
#endif // ifndef ballBallColDetect_h
