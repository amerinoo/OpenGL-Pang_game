/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef pangScenario_h
#define pangScenario_h
#include <iostream>
#include <vector>
#include <sstream>
#include "plane.h"
#include "ball.h"
#include "gravityForceGenerator.h"
#include "ballPlaneColDetect.h"
#include "ballBallColDetect.h"
#include "particleContact.h"
#include "character.h"
#include "constants.h"
using namespace std;

class PangScenario {
public:
    PangScenario();
    PangScenario(Plane left, Plane right, Plane bottom, int width, int height);
    PangScenario(const PangScenario &ps);
    void reset();
    void winner();
    void printScores(float width, float height, int i, char * name, char * strategyType);
    void printText(float width, float height, string str);
    void resetCharacter(int character);
    void integrate(double t);
    void checkColCharacterPlane(Character * character, Plane plane);
    void checkColCharacterBall(Character * character, Ball * ball);
    void checkColBallPlane(Ball * ball, Plane plane);
    void checkColBulletBall(Ball * ball, Character * character, int i);
    void checkColBallBall(Ball * ball, int i);
    void draw(int simulate = -1);
    void drawBackground();
    void shoot(PlayerID);
    void move(PlayerID, Action);

    Plane left;
    Plane right;
    Plane bottom;
    int width;
    int height;
    vector<Ball *> balls;
    vector<Character *> characters;
};
#endif // ifndef pangScenario_h
