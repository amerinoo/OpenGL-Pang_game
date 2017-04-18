/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "player.h"

Player::Player(){ }

Player::Player(const char * namee, PlayerID playerNumber, bool AIcontrolled)
    : playerNumber(playerNumber), AIcontrolled(AIcontrolled){
    strncpy(name, namee, MAX_LENGHT);
}

char * Player::getPlayerName(){ return name; }

PlayerID Player::getPlayerNumber(){ return playerNumber; }

bool Player::isAIControlled(){ return AIcontrolled; }
