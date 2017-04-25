/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "character.h"

Character::Character() : Particle(){ }

Character::Character(Vector3 position, double baseWidth, double height, Color color, int playerNumber)
    : Particle(1, position, Vector3()), baseWidth(baseWidth), height(height), color(color),
    score(0), lives(Constants::DEFAULT_LIVES), wins(0),
    playerNumber(playerNumber), isImmortal(false), textureSelected(0){
    textures = (playerNumber == PLAYER_1) ? Constants::linkTextures : Constants::marioTextures;

    stop();
}

void Character::setDimensions(double baseWidth, double height){
    this->baseWidth = baseWidth;
    this->height    = height;
}

void Character::setColor(Color color){ this->color = color; }

void Character::integrate(double time){
    Particle::integrate(time);
    if (hasBullet()) {
        bullet->integrate(time);
        if (!bullet->hasTTL(time)) bullet = NULL;
    }
    if (isImmortal) {
        timeImmortal -= time;
        isImmortal    = timeImmortal > 0;
    }
}

int Character::getPlayerNumber(){ return playerNumber; }

void Character::draw(){
    if (hasLives()) {
        double subPos = baseWidth / 2.0;

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[textureSelected]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(position.getX() - subPos, position.getY(), position.getZ());
        glTexCoord2f(0.0, 1.0);
        glVertex3f(position.getX() - subPos, position.getY() + height / 2.0, position.getZ());
        glTexCoord2f(1.0, 1.0);
        glVertex3f(position.getX() + subPos, position.getY() + height / 2.0, position.getZ());
        glTexCoord2f(1.0, 0.0);
        glVertex3f(position.getX() + subPos, position.getY(), position.getZ());
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        if (bullet != NULL) bullet->draw(); }
}

void Character::stop(){
    velocity        = Vector3();
    textureSelected = 0;
}

void Character::moveRight(double speed){
    velocity        = Vector3(speed, 0);
    textureSelected = 1;
}

void Character::moveLeft(double speed){
    velocity        = Vector3(-speed, 0);
    textureSelected = 2;
}

void Character::shoot(double time){
    if (!hasBullet() && hasLives()) bullet = new Bullet(position + Vector3(0, height), Vector3(0, 4), color, time);
}

bool Character::hasBullet(){ return bullet != NULL; }

void Character::removeBullet(){ bullet = NULL; }

int Character::getScore(){ return score; }

void Character::addScore(int score){ this->score += score; }

void Character::resetScore(){ this->score = 0; }

int Character::getLives(){ return lives; }

bool Character::hasLives(){ return lives > 0; }

void Character::setLives(int lives){ this->lives = lives; }

void Character::substractLive(){
    if (!isImmortal && hasLives()) {
        lives       -= 1;
        isImmortal   = true;
        timeImmortal = Constants::TIME_IMMORTAL;
        score       -= Constants::HIT_PUNISHMENT;
    }
}

int Character::getWins(){ return wins; }

void Character::addWin(){ wins += 1; }

Bullet * Character::getBullet(){ return bullet; }

Ball * Character::getMargin(){
    return new Ball(position + Vector3(0, height / 2.0), Vector3(), baseWidth / 2.0, Color::ball);
}
