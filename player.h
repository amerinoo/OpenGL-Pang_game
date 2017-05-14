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
#include "constants.h"
#include "ais.h"

class Player {
public:
    Player();
    Player(const char * name, PlayerID playerNumber, bool AIcontrolled, StrategyType strategyType, AI * ai);
    virtual bool getMovement(PangScenario * ps, Action * move) = 0;
    char * getPlayerName();
    PlayerID getPlayerNumber();
    bool isAIControlled();
    char * getStrategyTypeName();

    char name[MAX_LENGHT];
    PlayerID playerNumber;
    bool AIcontrolled;
    StrategyType strategyType;
    AI * ai;
};
#endif // ifndef player_h
