/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef heuristic_agent_ai_h
#define heuristic_agent_ai_h
#include "ai.h"

class HeuristicAI : public AI  {
public:
    HeuristicAI();
    virtual bool computeMove(PangScenario * ps, PlayerID playerNumber, Action * move);
};
#endif
