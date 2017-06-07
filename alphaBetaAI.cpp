/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */

#include "alphaBetaAI.h"

AlphaBetaAI::AlphaBetaAI() : AI(){ }

bool AlphaBetaAI::computeMove(PangScenario * ps, PlayerID playerNumber, Action * move){
    int actions_len = 2;
    Action actions[actions_len] = { LEFT, RIGHT };
    double bestAction = -HUGE_VAL;
    PlayerID Max      = playerNumber;
    PlayerID Min      = (playerNumber == PLAYER_1) ? PLAYER_2 : PLAYER_1;

    hasToShoot = false;

    PangScenario * psCopy = new PangScenario();
    pss.push_back(psCopy);
    for (int i = 0; i < actions_len; i++) {
        *psCopy = *ps;
        Action action = actions[i];
        psCopy->move(playerNumber, action);
        simulateMove(psCopy, Constants::REACTION_TIME);
        double points = AlphaBeta(psCopy, playerNumber, Constants::ALPHA_BETA_DEPTH, -HUGE_VAL, HUGE_VAL, Max, Min);
        if (points > bestAction) {
            bestAction = points;
            (*move)    = action;
        }
    }
    for (unsigned int i = 0; i < pss.size(); i++) {
        pss[i]->balls.clear();
        pss[i]->characters.clear();
    }
    return hasToShoot;
}

double AlphaBetaAI::AlphaBeta(PangScenario * ps, PlayerID playerNumber, int depth,
  double alpha, double beta, PlayerID Max, PlayerID Min){
    int actions_len = 2;
    Action actions[actions_len] = { LEFT, RIGHT };
    PangScenario * psCopy       = new PangScenario();

    pss.push_back(psCopy);
    if (depth == 0 || terminal(ps, playerNumber)) {
        return heuristic(ps, playerNumber);
    } else if (playerNumber == Max) {
        double bestValue = -HUGE_VAL;
        if (!ps->characters[playerNumber]->hasBullet()) {
            for (int i = 0; i < actions_len; i++) {
                *psCopy   = *ps;
                bestValue = max(bestValue, AlphaBeta(result(psCopy, actions[i], playerNumber, true),
                      Min, depth - 1, alpha, beta, Max, Min));
                if (bestValue >= beta) {
                    hasToShoot = true;
                    return bestValue;
                }

                alpha = max(alpha, bestValue);
            }
        }
        for (int i = 0; i < actions_len; i++) {
            *psCopy   = *ps;
            bestValue = max(bestValue, AlphaBeta(result(psCopy, actions[i], playerNumber, false),
                  Min, depth - 1, alpha, beta, Max, Min));
            if (bestValue >= beta) {
                hasToShoot = false;
                return bestValue;
            }

            alpha = max(alpha, bestValue);
        }


        return bestValue;
    } else {
        double bestValue = HUGE_VAL;
        if (!ps->characters[playerNumber]->hasBullet()) {
            for (int i = 0; i < actions_len; i++) {
                *psCopy   = *ps;
                bestValue = min(bestValue, AlphaBeta(result(psCopy, actions[i], playerNumber, true),
                      Max, depth - 1, alpha, beta, Max, Min));
                if (bestValue <= alpha) {
                    hasToShoot = true;
                    return bestValue;
                }

                beta = min(beta, bestValue);
            }
        }
        for (int i = 0; i < actions_len; i++) {
            *psCopy   = *ps;
            bestValue = min(bestValue, AlphaBeta(result(psCopy, actions[i], playerNumber, false),
                  Max, depth - 1, alpha, beta, Max, Min));
            if (bestValue <= alpha) {
                hasToShoot = false;
                return bestValue;
            }

            beta = min(beta, bestValue);
        }


        return bestValue;
    }
} // AlphaBeta

bool AlphaBetaAI::terminal(PangScenario * ps, PlayerID playerNumber){
    return !ps->characters[playerNumber]->hasLives() || ps->balls.empty();
}

PangScenario * AlphaBetaAI::result(PangScenario * ps, Action action, PlayerID playerNumber, bool shoot){
    ps->move(playerNumber, action);
    if (shoot) ps->shoot(playerNumber);
    simulateMove(ps, Constants::REACTION_TIME);
    return ps;
}
