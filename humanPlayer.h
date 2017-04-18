/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef human_player_h
#define human_player_h

#include "player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    HumanPlayer(const char * name, PlayerID playerNumber);
    bool getMovement(PangScenario * ps, Action * move);
};
#endif // ifndef human_player_h
