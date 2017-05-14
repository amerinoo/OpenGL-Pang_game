/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef game_h
#define game_h

#include "humanPlayer.h"
#include "botPlayer.h"
#include "pangScenario.h"

class Game  {
public:
    Game();
    Game(PangScenario * pangScenario);
    PangScenario * getPangScenario();
    void printScores(float width, float height, int i);
    void integrate(double t);
    void draw();
    void move(Player * player);
    void startGame();
    void pause();
    void changePlayerAI(PlayerID playerId, StrategyType type);

private:
    Player * createPlayer(PlayerID player, char * name, StrategyType type);
    AI * chooseAgent(StrategyType type, char * name);

    PangScenario * pangScenario;
    Player * player1;
    Player * player2;
    bool playing;
    bool simulate;
    vector<PangScenario *> pangScenarios;
};
#endif // ifndef game_h
