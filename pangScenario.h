/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef pangScenario_h
#define pangScenario_h
#include "plane.h"
#include "ball.h"
#include "gravityForceGenerator.h"
#include "ballPlaneColDetect.h"
#include "particleContact.h"

class PangScenario {
public:
    PangScenario();
    PangScenario(Plane left, Plane right, Plane bottom, Ball ball);
    void reset();
    void integrate(double t);
    void draw();

    Plane left;
    Plane right;
    Plane bottom;
    Ball ball;
    Vector3 initialBallPosition;
    Vector3 initialBallVelocity;
};
#endif // ifndef pangScenario_h
