/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef plane_h
#define plane_h
#include <cstdlib>
#include "vector3.h"

class Plane {
public:
    Plane();
    Plane(Vector3 vector, Vector3 point);
    double getDistance(Vector3 point);
    Vector3 getNormalVector();

private:
    double a;
    double b;
    double c;
    double d;
};
#endif // ifndef plane_h
