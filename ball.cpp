/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ball.h"

Ball::Ball(){ }

Ball::Ball(double mass, Vector3 position, Vector3 velocity, double radius, Color color)
    : Particle(mass, position, velocity), radius(radius), color(color){ }

double Ball::getRadius(){ return radius; }

Color Ball::getColor(){ return color; }

void Ball::setRadius(double radius){ this->radius = radius; }

void Ball::setColor(Color color){ this->color = color; }

void Ball::draw(){
    int segments = 20;

    glPushMatrix();

    glColor3f(color.red, color.green, color.blue);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(position.getX(), position.getY());
    for (int i = 0; i <= segments; i++) {
        float const t = 2 * M_PI * (float) i / (float) segments;
        glVertex2f(position.getX() + sin(t) * radius, position.getY() + cos(t) * radius);
    }
    glEnd();

    glPopMatrix();
}
