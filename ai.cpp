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

double AI::heuristic(PangScenario * ps, PlayerID playerNumber){
    double points         = 0;
    Character * character = ps->characters[playerNumber];
    Ball * ball = getBallPositionXClosest(ps, character);

    if (ball != NULL) points += fabs(character->getPosition().getX() - ball->getPosition().getX());
    points += character->getScore();
    points += 10 * character->getLives();

    return points;
}

Ball * AI::getBallPositionXClosest(PangScenario * ps, Character * character){
    Ball * mostCloseBall = NULL;
    double mostDangerousBallDistance = 9999;

    for (unsigned int i = 0; i < ps->balls.size(); i++) {
        Ball * ball     = ps->balls[i];
        double distance = fabs(character->getPosition().getX() - ball->getPosition().getX());
        if (isMoreClose(mostDangerousBallDistance, distance)) {
            mostCloseBall = ball;
            mostDangerousBallDistance = distance;
        }
    }
    return mostCloseBall;
}

bool AI::isMoreClose(double mostDangerousBallDistance, double distance){
    return mostDangerousBallDistance > distance;
}

void AI::simulateMove(PangScenario * ps, float timeLimit){
    elapsedTime = 0;

    this->timeLimit = timeLimit;
    while (elapsedTime < timeLimit) {
        tZero     = HUGE_VAL;
        colDetect = NULL;

        for (unsigned int i = 0; i < ps->characters.size(); i++) {
            Character * character = ps->characters[i];
            checkColCharPlaneVert(character, ps->left);
            checkColCharPlaneVert(character, ps->right);
        }

        for (unsigned int i = 0; i < ps->balls.size(); i++) {
            Ball * ball = ps->balls[i];

            checkColBallPlaneVert(ball, ps->left);
            checkColBallPlaneVert(ball, ps->right);
            checkColBallPlaneHoriz(ball, ps->bottom);
            for (unsigned int j = 0; j < ps->characters.size(); j++) {
                Character * character = ps->characters[j];
                checkColCharBall(character, ball);
                checkColBulletBall(ps, ball, character, i);
            }
            checkColBallBall(ps, ball, i);
        }

        if (colDetect == NULL) {
            resolve(ps, timeLimit - elapsedTime);
            break;
        } else {
            if (tZero < 0.02) tZero = 0.02;
            resolve(ps, tZero);
        }
        switch (colType) {
            case CHAR_PLANE:
                // std::cout << "CHAR_PLANE" << '\n';
                colDetect->resolve(chara);
                chara->stop();
                break;
            case BALL_CHAR:
                chara->substractLive();
                // std::cout << "BALL_CHAR " << chara->getLives() << '\n';
                ps->resetCharacter(chara->getPlayerNumber());
                break;
            case BALL_VERT:
            case BALL_BALL:
            case BALL_HORIZ:
                // std::cout << "BALL" << '\n';
                colDetect->resolve();
                break;
            case BALL_PROJ:
                // std::cout << "BALL_PROJ" << '\n';
                double points = balli->split(ps->balls, balli, colDetect);

                ps->balls.erase(ps->balls.begin() + ballIndex);
                chara->removeBullet();
                if (ps->balls.size() == 0) {
                    chara->addScore(points + Constants::LAST_BALL_POINTS);
                    elapsedTime = timeLimit;
                } else {
                    chara->addScore(points);
                }
                break;
        }
        if (colDetect) delete(colDetect);
        elapsedTime += tZero;
    }
} // simulateMove

void AI::resolve(PangScenario * ps, float t){
    double x, y, vx, vy;

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
        vx = ball->getVelocity().getX();
        vy = ball->getVelocity().getY() - 9.8 * t;
        ball->setVelocity(Vector3(vx, vy));
    }
}

void AI::checkColBallPlaneVert(Ball * ball, Plane plane){
    if (ball->getVelocity().getX() != 0) {
        double t = (plane.getX() - ball->getPosition().getX()) / ball->getVelocity().getX();
        if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
            double x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
            double y = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
            double d = plane.getDistance(Vector3(x, y));
            ParticleContact * particleContact = BallPlaneColDetect().
              getParticleContact(ball, plane, d);
            if (particleContact != NULL) {
                tZero     = t;
                colDetect = particleContact;
                colType   = BALL_VERT;
            }
        }
    }
}

void AI::checkColCharPlaneVert(Character * character, Plane plane){
    Ball * ball = character->getMargin();

    if (ball->getVelocity().getX() != 0) {
        double t = (plane.getX() - ball->getPosition().getX()) / ball->getVelocity().getX();
        if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
            double x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
            double y = ball->getPosition().getY();
            double d = plane.getDistance(Vector3(x, y));
            ParticleContact * particleContact = BallPlaneColDetect().
              getParticleContact(ball, plane, d);
            if (particleContact != NULL) {
                tZero = t;
                if (colDetect) delete(colDetect);
                colDetect = particleContact;
                colType   = CHAR_PLANE;
                chara     = character;
            }
        }
    }
}

void AI::checkColBallPlaneHoriz(Ball * ball, Plane plane){
    double vy  = ball->getVelocity().getY();
    double py  = ball->getPosition().getY();
    double sqr = sqrt(vy * vy + 4 * 4.9 * py);
    double t   = (vy + sqr) / 9.8;

    // double t2  = (vy - sqr) / 9.8;
    // double t   = (t1 > t2) ? t1 : t2;

    if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
        double x = ball->getPosition().getX() + ball->getVelocity().getX() * t;
        double y = ball->getPosition().getY() + ball->getVelocity().getY() * t - 4.9 * t * t;
        double d = fabs(plane.getDistance(Vector3(x, y)));
        ParticleContact * particleContact = BallPlaneColDetect().
          getParticleContact(ball, plane, d);
        if (particleContact != NULL) {
            tZero = t;
            if (colDetect) delete(colDetect);
            colDetect = particleContact;
            colType   = BALL_HORIZ;
        }
    }
}

void AI::checkColBulletBall(PangScenario * ps, Ball * ball, Character * character, int i){
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
                tZero = t;
                if (colDetect) delete(colDetect);
                colDetect = particleContact;
                colType   = BALL_PROJ;
                balli     = ball;
                ballIndex = i;
                chara     = character;
            }
        }
    }
}

void AI::checkColBallBall(PangScenario * ps, Ball * ball, int i){
    for (unsigned int j = i + 1; ball != NULL && j < ps->balls.size(); j++) {
        Ball * ball2 = ps->balls[j];
        checkColBallBall(ball, ball2);
    }
}

void AI::checkColBallBall(Ball * ball1, Ball * ball2){
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
            tZero = t;
            if (colDetect) delete(colDetect);
            colDetect = particleContact;
            colType   = BALL_BALL;
        }
    }
}

void AI::checkColCharBall(Character * character, Ball * ball2){
    Ball * ball1 = character->getMargin();
    double t     = (ball1->getPosition().getX() - ball2->getPosition().getX())
      / (ball2->getVelocity().getX() - ball1->getVelocity().getX());

    if (t > 0 && t < tZero && t + elapsedTime < timeLimit) {
        double y1 = ball1->getPosition().getY();
        double y2 = ball2->getPosition().getY() + ball2->getVelocity().getY() * t - 4.9 * t * t;
        double d  = fabs(y1 - y2);
        Vector3 normalVector = Vector3(0, y1 - y2);
        ParticleContact * particleContact = BallBallColDetect().
          getParticleContact(ball1, ball2, d, normalVector);
        if (particleContact != NULL) {
            tZero = t;
            if (colDetect) delete(colDetect);
            colDetect = particleContact;
            colType   = BALL_CHAR;
            chara     = character;
        }
    }
}

double AI::getRandomTargetPosition(){ return rand() / (double) RAND_MAX * Constants::DEFAULT_WIDTH; }
