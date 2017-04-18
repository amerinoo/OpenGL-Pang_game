/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef game_h
#define game_h

#include "humanPlayer.h"
#include "pangScenario.h"

class Game  {
public:
    Game();
    Game(PangScenario * pangScenario);
    PangScenario * getPangScenario();
    void printScores(float width, float height, int i);
    void integrate(double t);
    void startGame();

private:
    PangScenario * pangScenario;
    Player * player1;
    Player * player2;
    bool playing;
};
#endif // ifndef game_h
