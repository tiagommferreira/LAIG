#ifndef __CGFExample__Game__
#define __CGFExample__Game__

#include <stdio.h>
#include "Board.h"

class Game{
private:
    int currentPlayer;
    int currentPlay;
public:
    Game() {
        this->currentPlayer = 1;
        this->currentPlay = 0;
    }
    void setCurrentPlayer(int player);
    int getCurrentPlayer();
    void setCurrentPlay(int currentPlay);
    int getCurrentPlay();
};

#endif /* defined(__CGFExample__Game__) */
