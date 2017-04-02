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
#include "character.h"
using namespace std;

class PangScenario {
public:
    PangScenario();
    PangScenario(Plane left, Plane right, Plane bottom);
    void reset();
    void integrate(double t);
    void checkColCharacterPlane(Character * player, Plane plane);
    void checkColCharacterBall(Character * player, Ball * ball);
    void checkColBallPlane(Ball * ball, Plane plane);
    void checkColBulletBall(Ball * ball, Character * player, int i);
    void checkColBallBall(Ball * ball, int i);
    void draw();
    void shoot();
    void move(int);

    Plane left;
    Plane right;
    Plane bottom;
    vector<Ball *> balls;
    Character * player;
};
#endif // ifndef pangScenario_h
