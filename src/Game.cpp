//
//  Game.cpp
//  CGFExample
//
//  Created by Ricardo Loureiro on 16/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

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