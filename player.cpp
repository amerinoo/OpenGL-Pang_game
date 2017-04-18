/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "player.h"

Player::Player(){ }

Player::Player(const char * namee, int playerNumber, bool AIcontrolled)
    : playerNumber(playerNumber), AIcontrolled(AIcontrolled){
    strncpy(name, namee, MAX_LENGHT);
}

char * Player::getPlayerName(){ return name; }

int Player::getPlayerNumber(){ return playerNumber; }
