/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"

Game::Game(){ }

Game::Game(PangScenario * pangScenario) : pangScenario(pangScenario){
    player1 = new HumanPlayer("Player 1", 0);
    player2 = new HumanPlayer("Player 2", 1);
}

PangScenario * Game::getPangScenario(){ return pangScenario; }

void Game::integrate(double t){
    pangScenario->integrate(t);
}

void Game::startGame(){
    pangScenario->reset();
    playing = true;
}

void Game::printScores(float width, float height, int i){
    Player * player = (i == 0) ? player1 : player2;

    pangScenario->printScores(width, height, i, player->getPlayerName());
}
