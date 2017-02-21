/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "particleContact.h"

ParticleContact::ParticleContact(Particle * particle1, Particle * particle2, Vector3 contactNormal,
  double interpenetration) : particle1(particle1), particle2(particle2), contactNormal(contactNormal),
    interpenetration(interpenetration){ }
