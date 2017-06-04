/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef alpha_beta_agent_ai_h
#define alpha_beta_agent_ai_h
#include "ai.h"

class AlphaBetaAI : public AI  {
public:
    AlphaBetaAI();
    virtual bool computeMove(PangScenario * ps, PlayerID playerNumber, Action * move);
    double AlphaBeta(PangScenario * ps, PlayerID playerNumber, int depth,
      double alpha, double beta, PlayerID Max, PlayerID Min);
    bool terminal(PangScenario * ps, PlayerID playerNumber);
    PangScenario * result(PangScenario * ps, Action action, PlayerID playerNumber, bool shoot);

    bool hasToShoot;
    vector<PangScenario*> pss;
};
#endif // ifndef alpha_beta_agent_ai_h
