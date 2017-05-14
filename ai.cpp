/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */

#include "ai.h"

AI::AI() : targetPosition(getRandomTargetPosition()){ }

bool AI::computeMove(PangScenario * ps, PlayerID playerNumber, Action * move){
    Character * character = ps->characters[playerNumber];
    Vector3 position      = character->getPosition();
    double separation     = position.getX() - targetPosition;

    (*move) = (separation > 0) ? LEFT : RIGHT;
    if (fabs(separation) <= Constants::EPSILON) {
        targetPosition = getRandomTargetPosition();
        (*move)        = STOP;
    }

    return !character->hasBullet();
}

void AI::simulateMove(PangScenario * ps, float timeLimit){
    elapsedTime = 0;

    this->timeLimit = timeLimit;
    while (elapsedTime < timeLimit) {
        tZero     = HUGE_VAL;
        colDetect = NULL;

        for (unsigned int i = 0; i < ps->characters.size(); i++) {
            Character * character = ps->characters[i];
            if (checkColBallPlaneVert(character->getMargin(), ps->left) ||
              checkColBallPlaneVert(character->getMargin(), ps->right))
            {
                double x = character->getPosition().getX() + character->getVelocity().getX() * tZero;
                double y = character->getPosition().getY();
                character->setPosition(Vector3(x, y));
                colDetect->resolve(character);
                character->stop();
            }
        }

        for (unsigned int i = 0; i < ps->balls.size(); i++) {
            Ball * ball = ps->balls[i];

            checkColBallPlaneVert(ball, ps->left);
            checkColBallPlaneVert(ball, ps->right);
            checkColBallPlaneHoriz(ball, ps->bottom);
            for (unsigned int j = 0; j < ps->characters.size(); j++) {
                Character * character = ps->characters[j];
                if (checkColBallBall(character->getMargin(), ball)) {
                    character->substractLive();
                    ps->resetCharacter(character->getPlayerNumber());
                }
                if (checkColBulletBall(ps, ball, character, i)) {
                    double points = ball->split(ps->balls, ball, colDetect);

                    ps->balls.erase(ps->balls.begin() + i);
                    character->removeBullet();
                    ball = NULL;
                    if (ps->balls.size() == 0) {
                        character->addScore(points + Constants::LAST_BALL_POINTS);
                        // ps->winner();
                        // ps->reset();
                    } else {
                        character->addScore(points);
                    }
                }
            }
            checkColBallBall(ps, ball, i);
        }

        if (colDetect == NULL) {
            resolve(ps, timeLimit - elapsedTime);
            break;
        } else {
            resolve(ps, tZero);
        }

        colDetect->resolve();
        elapsedTime += tZero;
    }
} // simulateMove

void AI::resolve(PangScenario * ps, float t){
    double x, y;

    for (unsigned int i = 0; i < ps->characters.size(); i++) {
        Character * character = ps->characters[i];
        x = character->getPosition().getX() + character->getVelocity().getX() * t;
        y = character->getPosition().getY();
        character->setPosition(Vector3(x, y));
        if (character->hasBullet()) {
            Bullet * bullet = character->getBullet();
            x = bullet->getPosition().getX();
            y = bullet->getPosition().getY() + bullet->getVelocity().getY() * t;
            bullet->setPosition(Vector3(x, y));
        }
    }

    for (unsigned int i = 0; i < ps->balls.size(); i++) {
        Ball * ball = ps->balls[i];
        x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
        y = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
        ball->setPosition(Vector3(x, y));
    }
}

bool AI::checkColBallPlaneVert(Ball * ball, Plane plane){
    bool ret = false;

    if (ball->getVelocity().getX() != 0) {
        double t = fabs((plane.getX() - ball->getPosition().getX()) / ball->getVelocity().getX());
        if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
            double x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
            double y = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
            double d = plane.getDistance(Vector3(x, y));
            ParticleContact * particleContact = BallPlaneColDetect().
              getParticleContact(ball, plane, d);
            if (particleContact != NULL) {
                tZero     = t;
                colDetect = particleContact;
                ret       = true;
            }
        }
    }
    return ret;
}

void AI::checkColBallPlaneHoriz(Ball * ball, Plane plane){
    double vy  = ball->getVelocity().getY();
    double py  = ball->getPosition().getY();
    double sqr = sqrt(vy * vy + 4 * 4.9 * py);
    double t1  = (vy + sqr) / 9.8;
    double t2  = (vy - sqr) / 9.8;
    double t   = (t1 > t2) ? t1 : t2;

    if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
        double x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
        double y = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
        double d = fabs(plane.getDistance(Vector3(x, y)));
        ParticleContact * particleContact = BallPlaneColDetect().
          getParticleContact(ball, plane, d);
        if (particleContact != NULL) {
            tZero     = t;
            colDetect = particleContact;
        }
    }
}

bool AI::checkColBulletBall(PangScenario * ps, Ball * ball, Character * character, int i){
    bool ret = false;

    if (character->hasBullet()) {
        Bullet * bullet = character->getBullet();
        double t        = (bullet->getPosition().getX() - ball->getPosition().getX()) / ball->getVelocity().getX();
        if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
            double y1 = bullet->getPosition().getY() + bullet->getVelocity().getY() * t;
            double y2 = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
            double d  = fabs(y1 - y2);
            Vector3 normalVector = Vector3(0, y1 - y2);
            ParticleContact * particleContact = BallBallColDetect().
              getParticleContact(bullet, ball, d, normalVector);
            if (particleContact != NULL) {
                tZero     = t;
                colDetect = particleContact;
                ret       = true;
            }
        }
    }
    return ret;
}

void AI::checkColBallBall(PangScenario * ps, Ball * ball, int i){
    for (unsigned int j = i + 1; ball != NULL && j < ps->balls.size(); j++) {
        Ball * ball2 = ps->balls[j];
        checkColBallBall(ball, ball2);
    }
}

bool AI::checkColBallBall(Ball * ball1, Ball * ball2){
    bool ret = false;
    double t = (ball1->getPosition().getX() - ball2->getPosition().getX())
      / (ball2->getVelocity().getX() - ball1->getVelocity().getX());

    if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
        double y1 = ball1->getPosition().getY() + ball1->getVelocity().getY() * t - 4.9 * t * t;
        double y2 = ball2->getPosition().getY() + ball2->getVelocity().getY() * t - 4.9 * t * t;
        double d  = fabs(y1 - y2);
        Vector3 normalVector = Vector3(0, y1 - y2);
        ParticleContact * particleContact = BallBallColDetect().
          getParticleContact(ball1, ball2, d, normalVector);
        if (particleContact != NULL) {
            tZero     = t;
            colDetect = particleContact;
            ret       = true;
        }
    }
    return ret;
}

double AI::getRandomTargetPosition(){ return rand() % Constants::DEFAULT_WIDTH; }
