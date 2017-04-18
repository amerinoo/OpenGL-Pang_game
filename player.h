/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef player_h
#define player_h

#define MAX_LENGHT 32

#include <cstring>
#include "pangScenario.h"

class Player {
public:
    Player();
    Player(const char * name, int playerNumber, bool AIcontrolled);
    virtual bool getMovement(PangScenario * ps, int * move) = 0;
    char * getPlayerName();
    int getPlayerNumber();

private:
    char name[MAX_LENGHT];
    int playerNumber;
    bool AIcontrolled;
};
#endif // ifndef player_h
