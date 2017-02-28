/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ballBallColDetect.h"

BallBallColDetect::BallBallColDetect(){ }

ParticleContact * BallBallColDetect::getParticleContact(Ball * ball1, Ball * ball2){
    double d  = ball1->getDistance(ball2->getPosition());
    double dr = ball1->getRadius() + ball2->getRadius();
    Vector3 normalVector = ball1->getPosition() - ball2->getPosition();

    normalVector.normalize();
    if (d == dr) {
        return new ParticleContact(ball1, ball2, normalVector);
    } else if (d < dr) {
        return new ParticleContact(ball1, ball2, normalVector, dr - d);
    } else {
        return NULL;
    }
}
