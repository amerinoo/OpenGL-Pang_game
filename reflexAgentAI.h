/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef reflex_agent_ai_h
#define reflex_agent_ai_h
#include "ai.h"

class ReflexAgentAI : public AI  {
public:
    ReflexAgentAI();
    virtual bool computeMove(PangScenario * ps, PlayerID playerNumber, Action * move);
    Ball * getMostDangerousBall(PangScenario * ps, Character * character);
    Ball * getBallPositionXClosest(PangScenario * ps, Character * character);
    bool isFalling(Ball * ball);
    bool isInsideTheSafetyZone(double distance);
    bool isMoreClose(double mostDangerousBallDistance, double distance);
    bool haveToShoot(PangScenario * ps, Character * character);
    bool isBallInsideTheCone(Character * character, Ball * ball);
    bool approachingToTheVertical(Character * character, Ball * ball);
};
#endif // ifndef reflex_agent_ai_h
