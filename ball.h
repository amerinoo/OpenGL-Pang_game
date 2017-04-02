/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ball_h
#define ball_h
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "particle.h"
#include "color.h"
#include "ball.h"
#include "particleContact.h"
using namespace std;

class Ball : public Particle {
public:
    static const double little;
    static const double medium;
    static const double big;

    Ball();
    Ball(Vector3 position, Vector3 velocity, double radius, Color color);

    double getRadius();
    Color getColor();

    void setRadius(double radius);
    void setColor(Color color);

    void draw();
    double calculateMass(double radius);
    void split(vector<Ball *> &balls, Ball * ball, ParticleContact * particleContactBall);
private:

    double radius;
    Color color;
};
#endif // ifndef ball_h
