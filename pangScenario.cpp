/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "pangScenario.h"

PangScenario::PangScenario(){ }

PangScenario::PangScenario(Plane left, Plane right, Plane bottom)
    : left(left), right(right), bottom(bottom){
    player = new Character(Vector3(3, 0), 0.2, 0.3, Color::player);
    reset();
}

void PangScenario::reset(){
    Vector3 initialPosition(4, 4);
    Vector3 initialVelocity(3, 0);

    balls.clear();
    balls.push_back(new Ball(initialPosition, initialVelocity, Ball::big, Color::ball));
    player->removeBullet();
}

void PangScenario::integrate(double t){
    player->integrate(t);
    checkColCharacterPlane(player, left);
    checkColCharacterPlane(player, right);

    for (unsigned int i = 0; i < balls.size(); i++) {
        Ball * ball = balls[i];
        ball->clearForceAccumulator();
        GravityForceGenerator gfg;
        gfg.updateForce(ball);
        ball->integrate(t);

        checkColCharacterBall(player, ball);

        checkColBallPlane(ball, left);
        checkColBallPlane(ball, right);
        checkColBallPlane(ball, bottom);

        checkColBulletBall(ball, player, i);

        checkColBallBall(ball, i);
    }
} // integrate

void PangScenario::checkColCharacterPlane(Character * player, Plane plane){
    BallPlaneColDetect ballPlaneColDetect;
    ParticleContact * particleContactLeft = ballPlaneColDetect.getParticleContact(player->getMargin(), plane);

    if (particleContactLeft != NULL) {
        particleContactLeft->resolve();
        player->stop();
    }
}

void PangScenario::checkColCharacterBall(Character * player, Ball * ball){
    BallBallColDetect ballBallColDetect;
    ParticleContact * particleContactCharacter = ballBallColDetect.getParticleContact(player->getMargin(), ball);

    if (particleContactCharacter != NULL) {
        std::cout << "YOU LOOOSE" << std::endl;
        reset();
    }
}

void PangScenario::checkColBallPlane(Ball * ball, Plane plane){
    BallPlaneColDetect ballPlaneColDetect;
    ParticleContact * particleContact = ballPlaneColDetect.getParticleContact(ball, plane);

    if (particleContact != NULL) particleContact->resolve();
}

void PangScenario::checkColBulletBall(Ball * ball, Character * player, int i){
    BallBallColDetect ballBallColDetect;

    if (player->hasBullet()) {
        ParticleContact * particleContactBall = ballBallColDetect.getParticleContact(ball, player->getBullet());
        if (particleContactBall != NULL) {
            ball->split(balls, ball, particleContactBall);
            balls.erase(balls.begin() + i);
            player->removeBullet();
            ball = NULL;
            if (balls.size() == 0) {
                std::cout << "YOU WIIIN!" << std::endl;
                reset();
            }
        }
    }
} // checkColBulletBall

void PangScenario::checkColBallBall(Ball * ball, int i){
    BallBallColDetect ballBallColDetect;

    for (unsigned int j = i + 1; ball != NULL && j < balls.size(); j++) {
        Ball * ball2 = balls[j];
        ParticleContact * particleContactBall = ballBallColDetect.getParticleContact(ball, ball2);
        if (particleContactBall != NULL) particleContactBall->resolve();
    }
}

void PangScenario::draw(){
    for (unsigned int i = 0; i < balls.size(); i++)
        balls[i]->draw();

    player->draw();
}

void PangScenario::shoot(){ player->shoot(); }

void PangScenario::move(int i){
    double speed = 2;

    switch (i) {
        case 0:
            player->moveLeft(speed);
            break;
        case 1:
            player->moveRight(speed);
            break;
    }
}
