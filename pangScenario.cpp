/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "pangScenario.h"

PangScenario::PangScenario(){ }

PangScenario::PangScenario(Plane left, Plane right, Plane bottom, int width, int height)
    : left(left), right(right), bottom(bottom), width(width), height(height){
    characters.push_back(new Character(Vector3(width * 0.75, 0),
          Constants::CHARACTER_BASE_WIDTH, Constants::CHARACTER_HEIGHT, Color::player1, PLAYER_1));
    characters.push_back(new Character(Vector3(width * 0.25, 0),
          Constants::CHARACTER_BASE_WIDTH, Constants::CHARACTER_HEIGHT, Color::player2, PLAYER_2));
    reset();
}

PangScenario::PangScenario(const PangScenario &ps)
    : left(ps.left), right(ps.right), bottom(ps.bottom), width(ps.width), height(ps.height){
    for (unsigned int i = 0; i < ps.balls.size(); i++) balls.push_back(new Ball(*ps.balls[i]));
    for (unsigned int i = 0; i < ps.characters.size(); i++) characters.push_back(new Character(*ps.characters[i]));
}

PangScenario& PangScenario::operator = (const PangScenario& ps){
    left   = ps.left;
    right  = ps.right;
    bottom = ps.bottom;
    width  = ps.width;
    height = ps.height;
    balls.clear();
    characters.clear();
    for (unsigned int i = 0; i < ps.balls.size(); i++) balls.push_back(new Ball(*ps.balls[i]));
    for (unsigned int i = 0; i < ps.characters.size(); i++) characters.push_back(new Character(*ps.characters[i]));
    return *this;
}

void PangScenario::reset(){
    balls.clear();
    float wPos      = (rand() % 100) / 100.0;
    float wOtherPos = 1 - wPos;
    float hPos      = (rand() % 50 + 50) / 100.0;

    balls.push_back(new Ball(Vector3(width * wPos, height * hPos),
          Vector3(3, 0), Constants::BIG_BALL_SIZE, Color::ball));
    balls.push_back(new Ball(Vector3(width * wOtherPos, height * hPos),
          Vector3(-3, 0), Constants::BIG_BALL_SIZE, Color::ball));
    for (unsigned int i = 0; i < characters.size(); i++) {
        resetCharacter(i);
        characters[i]->setLives(Constants::DEFAULT_LIVES);
        characters[i]->resetScore();
    }
}

void PangScenario::winner(){
    if (characters[PLAYER_1]->getScore() > characters[PLAYER_2]->getScore()) characters[PLAYER_1]->addWin();
    else if (characters[PLAYER_1]->getScore() < characters[PLAYER_2]->getScore()) characters[PLAYER_2]->addWin();
}

void PangScenario::printScores(float width, float height, int i, char * name, char * strategyType){
    ostringstream text;
    Character * player = characters[i];

    text << name;
    text << " score: " << player->getScore();
    text << " lives: " << player->getLives();
    text << " wins: " << player->getWins();
    text << " strategy: " << strategyType;
    printText(width, height, text.str());
}

void PangScenario::printText(float width, float height, string str){
    glColor3f(1, 1, 1);
    glRasterPos2f(width, height);
    for (unsigned int i = 0; i < str.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }
}

void PangScenario::resetCharacter(int character){
    characters[character]->setPosition(Vector3(width * fabs(character - 0.75), 0));
    // characters[character]->removeBullet();
}

void PangScenario::integrate(double t){
    for (unsigned int i = 0; i < characters.size(); i++) {
        Character * character = characters[i];
        character->integrate(t);
        checkColCharacterPlane(character, left);
        checkColCharacterPlane(character, right);
    }

    for (unsigned int i = 0; i < balls.size(); i++) {
        Ball * ball = balls[i];
        ball->clearForceAccumulator();
        GravityForceGenerator gfg;
        gfg.updateForce(ball);
        ball->integrate(t);


        checkColBallPlane(ball, left);
        checkColBallPlane(ball, right);
        checkColBallPlane(ball, bottom);
        for (unsigned int j = 0; j < characters.size(); j++) {
            Character * character = characters[j];
            checkColCharacterBall(character, ball);
            checkColBulletBall(ball, character, i);
        }
        checkColBallBall(ball, i);
    }
    if (!characters[PLAYER_1]->hasLives() && !characters[PLAYER_2]->hasLives()) {
        winner();
        reset();
    }
} // integrate

void PangScenario::checkColCharacterPlane(Character * character, Plane plane){
    BallPlaneColDetect ballPlaneColDetect;
    ParticleContact * particleContactLeft = ballPlaneColDetect.getParticleContact(character->getMargin(), plane);

    if (particleContactLeft != NULL) {
        particleContactLeft->resolve(character);
        character->stop();
    }
}

void PangScenario::checkColCharacterBall(Character * character, Ball * ball){
    BallBallColDetect ballBallColDetect;
    ParticleContact * particleContactCharacter = ballBallColDetect.getParticleContact(character->getMargin(), ball);

    if (particleContactCharacter != NULL) {
        character->substractLive();
        resetCharacter(character->getPlayerNumber());
    }
}

void PangScenario::checkColBallPlane(Ball * ball, Plane plane){
    BallPlaneColDetect ballPlaneColDetect;
    ParticleContact * particleContact = ballPlaneColDetect.getParticleContact(ball, plane);

    if (particleContact != NULL) particleContact->resolve();
}

void PangScenario::checkColBulletBall(Ball * ball, Character * character, int i){
    BallBallColDetect ballBallColDetect;

    if (character->hasBullet()) {
        ParticleContact * particleContactBall = ballBallColDetect.getParticleContact(ball, character->getBullet());
        if (particleContactBall != NULL) {
            double points = ball->split(balls, ball, particleContactBall);
            balls.erase(balls.begin() + i);
            character->removeBullet();
            if (balls.size() == 0) {
                std::cout << "Game ends" << '\n';
                character->addScore(points + Constants::LAST_BALL_POINTS);
                winner();
                reset();
            } else {
                character->addScore(points);
            }
        }
    }
} // checkColBulletBall

void PangScenario::checkColBallBall(Ball * ball, int i){
    BallBallColDetect ballBallColDetect;

    for (unsigned int j = i + 1; ball != NULL && j < balls.size(); j++) {
        Ball * ball2 = balls[j];
        ParticleContact * particleContactBall = ballBallColDetect.getParticleContact(ball, ball2);
        if (particleContactBall != NULL) particleContactBall->resolve();
    }
}

void PangScenario::draw(int simulate){
    if (simulate == -1) drawBackground();
    for (unsigned int i = 0; i < balls.size(); i++)
        balls[i]->draw(simulate);
    for (unsigned int i = 0; i < characters.size(); i++)
        characters[i]->draw(simulate);
}

void PangScenario::drawBackground(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BACKGROUND);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3i(0, 0, 0);
    glTexCoord2f(1.0, 0.0);
    glVertex3i(Constants::DEFAULT_WIDTH, 0, 0);
    glTexCoord2f(1.0, 1.0);
    glVertex3i(Constants::DEFAULT_WIDTH, Constants::DEFAULT_HEIGHT, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3i(0, Constants::DEFAULT_HEIGHT, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void PangScenario::shoot(PlayerID id){ characters[id]->shoot(); }

void PangScenario::move(PlayerID id, Action action){
    switch (action) {
        case LEFT:
            characters[id]->moveLeft(Constants::CHARACTER_SPEED);
            break;
        case RIGHT:
            characters[id]->moveRight(Constants::CHARACTER_SPEED);
            break;
        case STOP:
            characters[id]->stop();
            break;
    }
}
