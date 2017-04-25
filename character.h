/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef character_h
#define character_h
#include <GL/glut.h>
#include "particle.h"
#include "vector3.h"
#include "color.h"
#include "ball.h"
#include "bullet.h"

class Character : public Particle {
public:
    Character();
    Character(Vector3 position, double baseWidth, double height, Color color, int playerNumber);
    void setDimensions(double baseWidth, double height);
    void setColor(Color color);
    void integrate(double time);
    void draw();
    void stop();
    void moveRight(double speed);
    void moveLeft(double speed);
    void shoot(double time = 2);
    bool hasBullet();
    void removeBullet();
    int getScore();
    void addScore(int score);
    void resetScore();
    bool hasLives();
    int getLives();
    void setLives(int lives);
    void substractLive();
    int getWins();
    void addWin();
    int getPlayerNumber();

    Bullet * getBullet();
    Ball * getMargin();

private:
    double baseWidth;
    double height;
    Color color;
    Bullet * bullet;
    int score;
    int lives;
    int wins;
    int playerNumber;
    bool isImmortal;
    double timeImmortal;
    Texture * textures;
    int textureSelected;
};
#endif // ifndef character_h
