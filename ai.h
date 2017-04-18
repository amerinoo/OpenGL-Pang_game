/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ai_h
#define ai_h
#include "pangScenario.h"
#include "constants.h"
#include "vector3.h"

class AI  {
public:
    AI();
    virtual bool computeMove(PangScenario * ps, PlayerID playerNumber, Action * move);
    double getRandomTargetPosition();
private:
    double targetPosition;
};
#endif // ifndef ai_h
