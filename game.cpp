/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"

Game::Game(){ }

Game::Game(PangScenario * pangScenario) : pangScenario(pangScenario){
    player1 = createPlayer(PLAYER_1, Constants::player1Name, Constants::strategyTypePlayer);
    player2 = createPlayer(PLAYER_2, Constants::player2Name, Constants::strategyTypeEnemy);
}

PangScenario * Game::getPangScenario(){ return pangScenario; }

void Game::integrate(double t){
    if (playing) {
        pangScenario->integrate(t);
        move(player1);
        move(player2);
    }
}

void Game::move(Player * player){
    if (player->isAIControlled()) {
        Action move;
        if (player->getMovement(pangScenario, &move))
            pangScenario->shoot(player->getPlayerNumber());
        pangScenario->move(player->getPlayerNumber(), move);
    }
}

void Game::startGame(){
    pangScenario->reset();
    playing = true;
}

void Game::printScores(float width, float height, int i){
    Player * player = (i == 0) ? player1 : player2;

    pangScenario->printScores(width, height, i, player->getPlayerName());
}

void Game::pause(){
    playing = !playing;
}

Player * Game::createPlayer(PlayerID player, char * name, StrategyType type){
    AI * ai = chooseAgent(type, name);

    if (ai == NULL) return new HumanPlayer(name, player);
    else return new BotPlayer(name, player, ai);
}

AI * Game::chooseAgent(StrategyType type, char * name){
    AI * ai = NULL;

    switch (type) {
        case HUMAN_AGENT:
            std::cout << "Human agent";
            break;
        case RANDOM_AGENT:
            std::cout << "Random agent";
            ai = new AI();
            break;
        case REFLEX_AGENT:
            std::cout << "Reflex agent";
            ai = new ReflexAgentAI();
            break;
    }
    std::cout << " chosen for " << name << '\n';
    return ai;
}
