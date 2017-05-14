/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef bullet_h
#define bullet_h
#include "ball.h"
#include "color.h"

class Bullet : public Ball {
public:
    Bullet();
    Bullet(Vector3 position, Vector3 velocity, Color color, double ttl);
    Bullet(const Bullet &b);

    void integrate(double t);
    bool hasTTL(double time);
private:
    double ttl;
};
#endif // ifndef bullet_h
