/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "ball.h"

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

double Ball::split(vector<Ball *> &balls, Ball * ball, ParticleContact * particleContactBall){
    Vector3 contactNormal        = particleContactBall->getContactNormal();
    Vector3 contactNormalRotated = Vector3(-contactNormal.getY(), contactNormal.getX());
    double points;
    double radius;

    if (this->radius == Constants::BIG_BALL_SIZE) {
        radius = Constants::MEDIUM_BALL_SIZE;
        points = Constants::BIG_BALL_POINTS;
    } else if (this->radius == Constants::MEDIUM_BALL_SIZE) {
        radius = Constants::SMALL_BALL_SIZE;
        points = Constants::MEDIUM_BALL_POINTS;
    } else if (this->radius == Constants::SMALL_BALL_SIZE) {
        radius = 0;
        points = Constants::SMALL_BALL_POINTS;
    }
    if (radius != 0) {
        balls.push_back(new Ball(ball->getPosition() + contactNormalRotated * radius,
              ball->getVelocity() + contactNormalRotated * Constants::VELOCITY_SEPARATOR, radius, Color::ball));
        balls.push_back(new Ball(ball->getPosition() - contactNormalRotated * radius,
              ball->getVelocity() - contactNormalRotated * Constants::VELOCITY_SEPARATOR, radius, Color::ball));
    }
    return points;
}
