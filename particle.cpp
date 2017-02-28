/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "particle.h"

Particle::Particle(){ }

Particle::Particle(double mass, Vector3 position, Vector3 velocity)
    : mass(mass), position(position), velocity(velocity){ }

double Particle::getMass(){ return mass; }

Vector3 Particle::getPosition(){ return position; }

Vector3 Particle::getVelocity(){ return velocity; }

void Particle::setMass(double mass){ this->mass = mass; }

void Particle::setPosition(Vector3 position){ this->position = position; }

void Particle::setVelocity(Vector3 velocity){ this->velocity = velocity; }

void Particle::integrate(double time){
    acceleration = forceAccumulator / mass;
    velocity     = velocity + acceleration * time;
    position     = position + velocity * time + acceleration * 0.5 * time * time;
}

void Particle::clearForceAccumulator(){
    forceAccumulator.setX(0);
    forceAccumulator.setY(0);
    forceAccumulator.setZ(0);
}

void Particle::addForce(Vector3 force){ forceAccumulator = forceAccumulator + force; }

double Particle::getDistance(Vector3 point){
    double a = position.getX() - point.getX();
    double b = position.getY() - point.getY();
    double c = position.getZ() - point.getZ();

    return sqrt(a * a + b * b + c * c);
}
