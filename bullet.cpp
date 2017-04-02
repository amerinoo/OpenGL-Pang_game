/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "bullet.h"

Bullet::Bullet() : Ball(){ }

Bullet::Bullet(Vector3 position, Vector3 velocity, Color color, double ttl)
    : Ball(position, velocity, 0.1, color), ttl(ttl){ }

void Bullet::integrate(double t){
    Ball::integrate(t);
    ttl -= t;
}

bool Bullet::hasTTL(double time){
    return ttl > 0;
}
