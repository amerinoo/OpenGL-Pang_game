/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ai_h
#define ai_h
#include <climits>
#include "pangScenario.h"
#include "constants.h"
#include "vector3.h"

class AI  {
public:
    AI();
    virtual bool computeMove(PangScenario * ps, PlayerID playerNumber, Action * move);
    void simulateMove(PangScenario * ps, float timeLimit);
    void resolve(PangScenario * ps, float t);
    bool checkColBallPlaneVert(Ball * ball, Plane plane);
    void checkColBallPlaneHoriz(Ball * ball, Plane plane);
    bool checkColBulletBall(PangScenario * ps, Ball * ball, Character * character, int i);
    void checkColBallBall(PangScenario * ps, Ball * ball, int i);
    bool checkColBallBall(Ball * ball1, Ball * ball2);
    double getRandomTargetPosition();
private:
    double targetPosition;
    double tZero;
    double elapsedTime;
    double timeLimit;
    ParticleContact * colDetect;
};
#endif // ifndef ai_h
