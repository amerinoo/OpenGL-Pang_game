/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef ball_h
#define ball_h
#include <GL/glut.h>
#include "particle.h"
#include "color.h"

class Ball : public Particle {
public:
    Ball();
    Ball(double mass, Vector3 position, Vector3 velocity, double radius, Color color);

    double getRadius();
    Color getColor();

    void setRadius(double radius);
    void setColor(Color color);

    void draw();
private:
    double radius;
    Color color;
};
#endif // ifndef ball_h
