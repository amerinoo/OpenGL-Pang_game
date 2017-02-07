/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "vector3.h"

Vector3::Vector3(){ }

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z){ }

double Vector3::getX(){
    return x;
}

double Vector3::getY(){
    return y;
}

double Vector3::getZ(){
    return z;
}

void Vector3::setX(double x){
    this->x = x;
}

void Vector3::setY(double y){
    this->y = y;
}

void Vector3::setZ(double z){
    this->z = z;
}

double Vector3::getModulus(){
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize(){
    double mod = getModulus();

    x = x / mod;
    y = y / mod;
    z = z / mod;
}

Vector3 Vector3::operator + (const Vector3& v){
    Vector3 vector;

    vector.x = this->x + v.x;
    vector.y = this->y + v.y;
    vector.z = this->z + v.z;
    return vector;
}

Vector3 Vector3::operator - (const Vector3& v){
    Vector3 vector;

    vector.x = this->x - v.x;
    vector.y = this->y - v.y;
    vector.z = this->z - v.z;
    return vector;
}

Vector3 Vector3::operator * (double n){
    Vector3 vector;

    vector.x = this->x * n;
    vector.y = this->y * n;
    vector.z = this->z * n;
    return vector;
}

double Vector3::operator * (const Vector3& v){
    return this->x * v.x + this->y * v.y + this->z * v.z;
}
