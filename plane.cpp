/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "plane.h"

Plane::Plane(){ }

Plane::Plane(Vector3 vector, Vector3 point){
    vector.normalize();
    a = vector.getX();
    b = vector.getY();
    c = vector.getZ();
    d = -a * point.getX() - b * point.getY() - c * point.getZ();
}

double Plane::getDistance(Vector3 point){
    return (a * point.getX() + b * point.getY() + c * point.getZ() + d) / sqrt(a * a + b * b + c * c);
}

Vector3 Plane::getNormalVector(){
    return Vector3(a, b, c);
}
