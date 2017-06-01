/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "player.h"

Player::Player(){ }

Player::Player(const char * namee, PlayerID playerNumber, bool AIcontrolled, StrategyType strategyType, AI * ai)
    : playerNumber(playerNumber), AIcontrolled(AIcontrolled), strategyType(strategyType), ai(ai){
    strncpy(name, namee, MAX_LENGHT);
}

char * Player::getPlayerName(){ return name; }

PlayerID Player::getPlayerNumber(){ return playerNumber; }

bool Player::isAIControlled(){ return AIcontrolled; }

char * Player::getStrategyTypeName(){
    switch (strategyType) {
        case HUMAN_AGENT:
            return (char *) "Human";

        case RANDOM_AGENT:
            return (char *) "Random";

        case REFLEX_AGENT:
            return (char *) "Reflex";

        case HEURISTIC_AGENT:
            return (char *) "Heuristic";
    }
    return (char *) "";
}
