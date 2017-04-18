/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "humanPlayer.h"

HumanPlayer::HumanPlayer(){ }

HumanPlayer::HumanPlayer(const char * name, int playerNumber)
    : Player(name, playerNumber, false){ }

bool HumanPlayer::getMovement(PangScenario * ps, int * move){ return false; }
