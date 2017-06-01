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
        simulate = true;
        pangScenario->integrate(t);
        move(player1);
        move(player2);
    } else {
        if (simulate) {
            pangScenarios.clear();
            PangScenario * p;
            float simus[] = { 0.1, 0.25, 0.5, 0.75, 1.0 };
            for (int i = 0; i < 5; i++) {
                p = new PangScenario(*pangScenario);
                player1->ai->simulateMove(p, simus[i]);
                pangScenarios.push_back(p);
            }
            simulate = false;
        }
    }
}

void Game::draw(){
    pangScenario->draw();
    if (!playing) {
        for (unsigned int i = 0; i < pangScenarios.size(); i++) {
            pangScenarios[i]->draw(i);
        }
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

    pangScenario->printScores(width, height, i, player->getPlayerName(), player->getStrategyTypeName());
}

void Game::pause(){
    playing = !playing;
}

void Game::changePlayerAI(PlayerID playerId, StrategyType type){
    if (playerId == PLAYER_1) player1 = createPlayer(playerId, player1->getPlayerName(), type);
    else player2 = createPlayer(playerId, player2->getPlayerName(), type);
    pangScenario->move(playerId, STOP);
}

Player * Game::createPlayer(PlayerID player, char * name, StrategyType type){
    AI * ai = chooseAgent(type, name);

    if (ai == NULL) return new HumanPlayer(name, player, type);
    else return new BotPlayer(name, player, type, ai);
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
        case HEURISTIC_AGENT:
            std::cout << "Heuristic agent";
            ai = new HeuristicAI();
            break;
    }
    std::cout << " chosen for " << name << '\n';
    return ai;
}
