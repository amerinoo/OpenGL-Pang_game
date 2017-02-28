/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef pangScenario_h
#define pangScenario_h
#include <iostream>
#include <vector>
#include "plane.h"
#include "ball.h"
#include "gravityForceGenerator.h"
#include "ballPlaneColDetect.h"
#include "ballBallColDetect.h"
#include "particleContact.h"
using namespace std;

class PangScenario {
public:
    PangScenario();
    PangScenario(Plane left, Plane right, Plane bottom, vector<Ball *> balls);
    void reset();
    void integrate(double t);
    void draw();

    Plane left;
    Plane right;
    Plane bottom;
    vector<Ball *> balls;
    // Vector3 initialBallPosition;
    // Vector3 initialBallVelocity;
};
#endif // ifndef pangScenario_h
