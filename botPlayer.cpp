/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "botPlayer.h"

BotPlayer::BotPlayer(){ }

BotPlayer::BotPlayer(const char * name, PlayerID playerNumber, AI * ai)
    : Player(name, playerNumber, true), ai(ai){ }

bool BotPlayer::getMovement(PangScenario * ps, Action * move){
    return ai->computeMove(ps, playerNumber, move);
}
