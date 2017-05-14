/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ballBallColDetect.h"

BallBallColDetect::BallBallColDetect(){ }

ParticleContact * BallBallColDetect::getParticleContact(Ball * ball1, Ball * ball2){
    double d = ball1->getDistance(ball2->getPosition());
    Vector3 normalVector = ball1->getPosition() - ball2->getPosition();

    return getParticleContact(ball1, ball2, d, normalVector);
}

ParticleContact * BallBallColDetect::getParticleContact(Ball * ball1, Ball * ball2,
  double d, Vector3 normalVector){
    double dr = ball1->getRadius() + ball2->getRadius();

    normalVector.normalize();

    if (d == dr) {
        return new ParticleContact(ball1, ball2, normalVector);
    } else if (d < dr) {
        return new ParticleContact(ball1, ball2, normalVector, dr - d);
    } else {
        return NULL;
    }
}
