/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef bot_player_h
#define bot_player_h

#include "player.h"
#include "ais.h"

class BotPlayer : public Player {
public:
    BotPlayer();
    BotPlayer(const char * name, PlayerID playerNumber, AI * ai);
    bool getMovement(PangScenario * ps, Action * move);
private:
    AI * ai;
};
#endif // ifndef bot_player_h
