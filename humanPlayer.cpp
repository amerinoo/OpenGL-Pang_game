/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "humanPlayer.h"

HumanPlayer::HumanPlayer(){ }

HumanPlayer::HumanPlayer(const char * name, PlayerID playerNumber, StrategyType strategyType)
    : Player(name, playerNumber, false, strategyType){ }

bool HumanPlayer::getMovement(PangScenario * ps, Action * move){ return false; }
