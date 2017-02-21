/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "pangScenario.h"

PangScenario::PangScenario(){ }

PangScenario::PangScenario(Plane left, Plane right, Plane bottom, Ball ball)
    : left(left), right(right), bottom(bottom), ball(ball),
    initialBallPosition(ball.getPosition()), initialBallVelocity(ball.getVelocity()){ }

#include <iostream>
void PangScenario::reset(){
    ball.setPosition(initialBallPosition);
    ball.setVelocity(initialBallVelocity);
}

void PangScenario::integrate(double t){
    ball.clearForceAccumulator();
    GravityForceGenerator gfg;
    gfg.updateForce(&ball);
    ball.integrate(t);
    BallPlaneColDetect ballPlaneColDetect;
    ParticleContact * particleContactLeft = ballPlaneColDetect.getParticleContact(&ball, left);
    if (particleContactLeft != NULL) particleContactLeft->resolve();
    ParticleContact * particleContactRight = ballPlaneColDetect.getParticleContact(&ball, right);
    if (particleContactRight != NULL) particleContactRight->resolve();
    ParticleContact * particleContactBottom = ballPlaneColDetect.getParticleContact(&ball, bottom);
    if (particleContactBottom != NULL) particleContactBottom->resolve();
}

void PangScenario::draw(){
    ball.draw();
}
