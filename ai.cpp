/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */

#include "ai.h"

AI::AI() : targetPosition(getRandomTargetPosition()){ }

#include <iostream>
bool AI::computeMove(PangScenario * ps, PlayerID playerNumber, Action * move){
    Character * character = ps->characters[playerNumber];
    Vector3 position      = character->getPosition();
    double separation     = position.getX() - targetPosition;

    (*move) = (separation > 0) ? LEFT : RIGHT;
    if (fabs(separation) < Constants::EPSILON) {
        targetPosition = getRandomTargetPosition();
        (*move)        = STOP;
    }

    return !character->hasBullet();
}

double AI::getRandomTargetPosition(){ return rand() % Constants::DEFAULT_WIDTH; }
