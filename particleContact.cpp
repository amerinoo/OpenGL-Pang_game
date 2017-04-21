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

void ParticleContact::resolve(Particle * character){
    particle1 = character;
    resolveInterpenetration();
}

void ParticleContact::resolveInterpenetration(){
    double displacement;

    if (particle2 == NULL) {
        displacement = interpenetration;
    } else {
        displacement = (particle1->getMass() * interpenetration) / ( particle1->getMass() + particle2->getMass() );
        Vector3 invContactNormal = contactNormal * -1;
        particle2->setPosition(particle2->getPosition() + invContactNormal * displacement);
        displacement = (particle2->getMass() * interpenetration) / ( particle1->getMass() + particle2->getMass() );
    }

    particle1->setPosition(particle1->getPosition() + contactNormal * displacement);
}

void ParticleContact::resolveVelocity(){
    Vector3 closingVel;
    Vector3 closingVelAB = contactNormal * (particle1->getVelocity() * contactNormal);

    if (particle2 == NULL) {
        closingVel = closingVelAB;
        particle1->setVelocity(particle1->getVelocity() - closingVel * 2);
    } else {
        Vector3 closingVelBA = contactNormal * (particle2->getVelocity() * contactNormal);
        double invA  = 1 / particle1->getMass();
        double invB  = 1 / particle2->getMass();
        double invAB = invA + invB;
        closingVel = closingVelAB - closingVelBA;
        particle1->setVelocity(particle1->getVelocity() - closingVel * invA / invAB * 2);
        particle2->setVelocity(particle2->getVelocity() + closingVel * invB / invAB * 2);
    }
}

Vector3 ParticleContact::getContactNormal(){ return contactNormal; }
