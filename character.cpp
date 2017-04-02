/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "character.h"

Character::Character() : Particle(){ }

Character::Character(Vector3 position, double baseWidth, double height, Color color)
    : Particle(1, position, Vector3()){
    setDimensions(baseWidth, height);
    setColor(color);
    stop();
}

void Character::setDimensions(double baseWidth, double height){
    this->baseWidth = baseWidth;
    this->height    = height;
}

void Character::setColor(Color color){ this->color = color; }

void Character::integrate(double time){
    Particle::integrate(time);
    if (bullet != NULL) {
        bullet->integrate(time);
        if (!bullet->hasTTL(time)) bullet = NULL;
    }
}

void Character::draw(){
    double subPos = baseWidth / 2.0;

    glPushMatrix();

    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_TRIANGLES);
    glVertex2f(position.getX(), height);
    glVertex2f(position.getX() + subPos, 0);
    glVertex2f(position.getX() - subPos, 0);
    glEnd();
    glPopMatrix();
    if (bullet != NULL) bullet->draw();
}

void Character::stop(){ velocity = Vector3(); }

void Character::moveLeft(double speed){ velocity = Vector3(-speed, 0); }

void Character::moveRight(double speed){ velocity = Vector3(speed, 0); }

void Character::shoot(double time){
    if (bullet == NULL) bullet = new Bullet(position + Vector3(0, height), Vector3(0, 4), Color::player, time);
}

bool Character::hasBullet(){ return bullet != NULL; }

void Character::removeBullet(){ bullet = NULL; }

Bullet * Character::getBullet(){ return bullet; }

Ball * Character::getMargin(){
    return new Ball(position + Vector3(0, height / 2.0), Vector3(), height / 2.0, Color::ball);
}
