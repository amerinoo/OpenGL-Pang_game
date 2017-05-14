/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ballPlaneColDetect.h"

BallPlaneColDetect::BallPlaneColDetect(){ }

ParticleContact * BallPlaneColDetect::getParticleContact(Ball * ball, Plane plane){
    double d = plane.getDistance(ball->getPosition());

    return getParticleContact(ball, plane, d);
}

ParticleContact * BallPlaneColDetect::getParticleContact(Ball * ball, Plane plane, double d){
    if (d == ball->getRadius()) {
        return new ParticleContact(ball, NULL, plane.getNormalVector());
    } else if (d < ball->getRadius()) {
        return new ParticleContact(ball, NULL, plane.getNormalVector(), ball->getRadius() - d);
    } else {
        return NULL;
    }
}
