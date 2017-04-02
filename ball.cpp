/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ball.h"

const double Ball::little = 0.2;
const double Ball::medium = 0.3;
const double Ball::big    = 0.4;

Ball::Ball(){ }

Ball::Ball(Vector3 position, Vector3 velocity, double radius, Color color)
    : Particle(calculateMass(radius), position, velocity), radius(radius), color(color){ }

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

double Ball::calculateMass(double radius){
    double density = 1;
    double volume  = 4 / 3.0 * M_PI * pow(radius, 3);

    return density * volume;
}

void Ball::split(vector<Ball *> &balls, Ball * ball, ParticleContact * particleContactBall){
    Vector3 contactNormal        = particleContactBall->getContactNormal();
    Vector3 contactNormalRotated = Vector3(-contactNormal.getY(), contactNormal.getX());
    double radius;

    if (this->radius == Ball::big) radius = Ball::medium;
    else if (this->radius == Ball::medium) radius = Ball::little;
    else if (this->radius == Ball::little) radius = 0;
    if (radius != 0) {
        double velocitySeparator = 5;
        balls.push_back(new Ball(ball->getPosition() + contactNormalRotated * radius,
              ball->getVelocity() + contactNormalRotated * velocitySeparator, radius, Color::ball));
        balls.push_back(new Ball(ball->getPosition() - contactNormalRotated * radius,
              ball->getVelocity() - contactNormalRotated * velocitySeparator, radius, Color::ball));
    }
}
