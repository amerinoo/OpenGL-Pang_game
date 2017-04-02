/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef character_h
#define character_h
#include <GL/glut.h>
#include "particle.h"
#include "vector3.h"
#include "color.h"
#include "ball.h"
#include "bullet.h"

class Character : public Particle {
public:
    Character();
    Character(Vector3 position, double baseWidth, double height, Color color);
    void setDimensions(double baseWidth, double height);
    void setColor(Color color);
    void integrate(double time);
    void draw();
    void stop();
    void moveLeft(double speed);
    void moveRight(double speed);
    void shoot(double time = 2);
    bool hasBullet();
    void removeBullet();

    Bullet * getBullet();
    Ball * getMargin();

private:
    double baseWidth;
    double height;
    Color color;
    Bullet * bullet;
};
#endif // ifndef character_h
