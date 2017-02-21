/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "particleContact.h"

ParticleContact::ParticleContact(Particle * particle1, Particle * particle2, Vector3 contactNormal,
  double interpenetration) : particle1(particle1), particle2(particle2), contactNormal(contactNormal),
    interpenetration(interpenetration){ }

void ParticleContact::resolve(){
    resolveInterpenetration();
    resolveVelocity();
}

void ParticleContact::resolveInterpenetration(){
    particle1->setPosition(particle1->getPosition() + contactNormal * interpenetration);
}

void ParticleContact::resolveVelocity(){
    Vector3 closingVel = contactNormal * (particle1->getVelocity() * contactNormal);

    particle1->setVelocity(particle1->getVelocity() - closingVel * 2);
}
