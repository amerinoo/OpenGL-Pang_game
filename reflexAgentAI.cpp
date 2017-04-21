/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "reflexAgentAI.h"

ReflexAgentAI::ReflexAgentAI() : AI(){ }

/*
 * If there is a most dangerous ball, the character must move away from that ball. Otherwise,
 * search the ball whose Position x coordinate is closest to the character position and move
 * towards that ball (to be able to shoot at it).
 */
bool ReflexAgentAI::computeMove(PangScenario * ps, PlayerID playerNumber, Action * move){
    Character * character = ps->characters[playerNumber];
    Ball * ball = getMostDangerousBall(ps, character);
    bool moveDecision;

    if (ball != NULL) {
        /* the character must move away from that ball */
        moveDecision = ball->getVelocity().getX() < 0;
    } else {
        /* search the ball whose Position x coordinate is closest
         * to the character position and move
         * towards that ball */
        ball         = getBallPositionXClosest(ps, character);
        moveDecision = character->getPosition().getX() - ball->getPosition().getX() < 0;
    }
    (*move) = (moveDecision) ? RIGHT : LEFT;

    return haveToShoot(ps, character);
}

/*
 * A dangerous ball is one that is falling (i.e.: its Velocity vector has a negative y)
 * and whose distance to the player character is lower than
 * some SAFETY_DISTANCE constant. Then, the most dangerous ball is simply the nearest
 * one.
 */
Ball * ReflexAgentAI::getMostDangerousBall(PangScenario * ps, Character * character){
    Ball * mostDangerousBall         = NULL;
    double mostDangerousBallDistance = 9999;

    for (unsigned int i = 0; i < ps->balls.size(); i++) {
        Ball * ball     = ps->balls[i];
        double distance = (character->getPosition() - ball->getPosition()).getModulus();
        if (isFalling(ball) && isInsideTheSafetyZone(distance) &&
          isMoreClose(mostDangerousBallDistance, distance))
        {
            mostDangerousBall         = ball;
            mostDangerousBallDistance = distance;
        }
    }
    return mostDangerousBall;
}

Ball * ReflexAgentAI::getBallPositionXClosest(PangScenario * ps, Character * character){
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

bool ReflexAgentAI::isFalling(Ball * ball){ return ball->getVelocity().getY() < 0; }

bool ReflexAgentAI::isInsideTheSafetyZone(double distance){
    return distance < Constants::SAFETY_DISTANCE;
}

bool ReflexAgentAI::isMoreClose(double mostDangerousBallDistance, double distance){
    return mostDangerousBallDistance > distance;
}

/*
 * If current time is less than the player last shot time plus the non-shooting period, the method
 * returns false (i.e. it cannot shoot).
 * If there is a ball inside a cone starting from the character that is
 * approaching to the vertical of the character (like B), then return true. Otherwise, return false.
 */
bool ReflexAgentAI::haveToShoot(PangScenario * ps, Character * character){
    for (unsigned int i = 0; i < ps->balls.size(); i++) {
        Ball * ball = ps->balls[i];
        if (isBallInsideTheCone(character, ball) && approachingToTheVertical(character, ball)) {
            return true;
        }
    }
    return false;
}

bool ReflexAgentAI::isBallInsideTheCone(Character * character, Ball * ball){
    double x = ball->getPosition().getX() - character->getPosition().getX();
    double y = ball->getPosition().getY() - character->getPosition().getY();

    return fabs(x) <= y * Constants::CONE_WIDTH;
}

bool ReflexAgentAI::approachingToTheVertical(Character * character, Ball * ball){
    bool isOnTheRightOfTheBall = character->getPosition().getX() > ball->getPosition().getX();
    bool isBallDirectionRight  = ball->getVelocity().getX() > 0;

    return (isOnTheRightOfTheBall && isBallDirectionRight) || (!isOnTheRightOfTheBall && !isBallDirectionRight);
    // if (isOnTheRightOfTheBall && isBallDirectionRight) {
    //     return true;
    // } else if (!isOnTheRightOfTheBall && !isBallDirectionRight)    {
    //     return true;
    // }
    // return false;
}
