
#include "Game.h"

void Game::setCurrentPlay(int currentPlay) {
    this->currentPlay = currentPlay;
}

void Game::setCurrentPlayer(int currentPlayer) {
    this->currentPlayer = currentPlayer;
}


int Game::getCurrentPlay() {
    return this->currentPlay;
}

int Game::getCurrentPlayer() {
    return this->currentPlayer;
}