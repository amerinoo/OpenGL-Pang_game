/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"

Game::Game(){ }

Game::Game(PangScenario * pangScenario) : pangScenario(pangScenario){
    player1 = new HumanPlayer("Player 1", PLAYER_1);
    player1 = new BotPlayer("Player 1", PLAYER_1, new AI());
    player2 = new BotPlayer("Player 2", PLAYER_2, new AI());
    player2 = new BotPlayer("Player 2", PLAYER_2, new ReflexAgentAI());
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
