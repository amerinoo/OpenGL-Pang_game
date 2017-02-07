/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef vector3_h
#define vector3_h
#include <cmath>

class Vector3 {
public:
    Vector3();
    Vector3(double x, double y, double z = 0);

    double getX();
    double getY();
    double getZ();

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double getModulus();
    void normalize();
    Vector3 operator + (const Vector3& v);
    Vector3 operator - (const Vector3& v);
    Vector3 operator * (double n);
    double operator * (const Vector3& v);

private:
    double x;
    double y;
    double z;
};
#endif // ifndef vector3_h
