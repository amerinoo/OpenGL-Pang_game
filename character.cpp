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

Character::Character(const Character &c) : Particle(c), baseWidth(c.baseWidth),
    height(c.height), color(c.color), score(c.score),
    lives(c.lives), wins(c.wins), playerNumber(c.playerNumber), isImmortal(c.isImmortal),
    textureSelected(c.textureSelected){
    bullet = (c.hasBullet()) ? new Bullet(*c.bullet) : NULL;
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

void Character::draw(int simulation){
    if (hasLives()) {
        // Safety zone
        // int i;
        // int lineAmount = 100; // # of triangles used to draw circle
        //
        // GLfloat radius  = Constants::SAFETY_DISTANCE; // radius
        // GLfloat twicePi = 2.0f * M_PI;
        //
        // glBegin(GL_LINE_LOOP);
        // for (i = 0; i <= lineAmount; i++) {
        //     glVertex2f(
        //       position.getX() + (radius * cos(i * twicePi / lineAmount)),
        //       position.getY() + (radius * sin(i * twicePi / lineAmount))
        //     );
        // }
        // glEnd();

        // Cone
        // glPushMatrix();
        // glBegin(GL_TRIANGLES);
        // glVertex2f(position.getX(), height / 2.0);
        // glVertex2f(position.getX() + Constants::CONE_WIDTH, 4);
        // glVertex2f(position.getX() - Constants::CONE_WIDTH, 4);
        // glEnd();
        // glBegin(GL_LINES);
        // glColor3f(1, 0, 0);
        // glVertex2f(position.getX(), height / 2.0);
        // glVertex2f(position.getX(), 4);
        // glEnd();
        // glPopMatrix();

        double subPos = baseWidth / 2.0;
        if (simulation != -1) {
            glPushMatrix();
            double red, blue;
            if (playerNumber == 1) {
                red  = simulation * 0.2;
                blue = 0;
            } else {
                red  = 0;
                blue = simulation * 0.2;
            }
            glColor3f(red, 0, blue);
            glBegin(GL_TRIANGLES);
            glVertex2f(position.getX(), height);
            glVertex2f(position.getX() + subPos, 0);
            glVertex2f(position.getX() - subPos, 0);
            glEnd();
            glPopMatrix();
        } else {
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
        }
        if (bullet != NULL) bullet->draw(simulation);
    }
} // draw

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
    if (!hasBullet() && hasLives()) {
        bullet = new Bullet(position + Vector3(0, height), Vector3(0, 4), color, time);
        score -= 10;
    }
}

bool Character::hasBullet() const { return bullet != NULL; }

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
    return new Ball(position + Vector3(0, height / 2.0), velocity, baseWidth / 2.0, Color::ball);
}
