/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "pangScenario.h"

PangScenario::PangScenario(){ }

PangScenario::PangScenario(Plane left, Plane right, Plane bottom, vector<Ball *> balls)
    : left(left), right(right), bottom(bottom), balls(balls){ }

// ,initialBallPosition(ball.getPosition()), initialBallVelocity(ball.getVelocity()){ }

void PangScenario::reset(){
    // ball.setPosition(initialBallPosition);
    // ball.setVelocity(initialBallVelocity);
}

void PangScenario::integrate(double t){
    for (unsigned int i = 0; i < balls.size(); i++) {
        Ball * ball = balls[i];
        ball->clearForceAccumulator();
        GravityForceGenerator gfg;
        gfg.updateForce(ball);
        ball->integrate(t);
        BallPlaneColDetect ballPlaneColDetect;
        BallBallColDetect ballBallColDetect;
        ParticleContact * particleContactLeft = ballPlaneColDetect.getParticleContact(ball, left);
        if (particleContactLeft != NULL) particleContactLeft->resolve();
        ParticleContact * particleContactRight = ballPlaneColDetect.getParticleContact(ball, right);
        if (particleContactRight != NULL) particleContactRight->resolve();
        ParticleContact * particleContactBottom = ballPlaneColDetect.getParticleContact(ball, bottom);
        if (particleContactBottom != NULL) particleContactBottom->resolve();
        for (unsigned int j = i + 1; j < balls.size(); j++) {
            Ball * ball2 = balls[j];
            ParticleContact * particleContactBall = ballBallColDetect.getParticleContact(ball, ball2);
            if (particleContactBall != NULL) particleContactBall->resolve();
        }
    }
}

void PangScenario::draw(){
    for (unsigned int i = 0; i < balls.size(); i++)
        balls[i]->draw();
}
