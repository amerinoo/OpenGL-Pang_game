/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */

#include "heuristicAI.h"

HeuristicAI::HeuristicAI() : AI(){ }

bool HeuristicAI::computeMove(PangScenario * ps, PlayerID playerNumber, Action * move){
    int actions_len = 3;
    Action actions[actions_len] = {  RIGHT, LEFT, STOP };
    double bestAction = -HUGE_VAL;
    bool shoot        = false;

    if (!ps->characters[playerNumber]->hasBullet()) {
        for (int i = 0; i < actions_len; i++) {
            PangScenario * psCopy = new PangScenario(*ps);
            Action action         = actions[i];
            psCopy->move(playerNumber, action);
            psCopy->shoot(playerNumber);
            simulateMove(psCopy, Constants::H_AI_TIME_LIMIT);
            double points = heuristic(psCopy, playerNumber);
            if (points > bestAction) {
                bestAction = points;
                (*move)    = action;
                shoot      = true;
            }
        }
    }
    for (int i = 0; i < actions_len; i++) {
        PangScenario * psCopy = new PangScenario(*ps);
        Action action         = actions[i];
        psCopy->move(playerNumber, action);
        simulateMove(psCopy, Constants::H_AI_TIME_LIMIT);
        double points = heuristic(psCopy, playerNumber);
        if (points > bestAction) {
            bestAction = points;
            (*move)    = action;
            shoot      = false;
        }
    }
    return shoot;
} // computeMove
