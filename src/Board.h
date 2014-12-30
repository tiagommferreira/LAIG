#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include <vector>
#include "Section.h"
#include "CGFappearance.h"
#include "Primitive.h"
#include "Stack.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class Board: public Primitive {
private:
    Section* section;
    vector<vector< Stack *> > currentState;
    vector<vector<int> >selected;
public:
    void resetBoardColours();
    void changeColours(char* points);
    void updateBoard(char* board, vector<int> pointsClicked);
    void updateBoard2(char* board);
    string boardToString();
    void setPosition(int x, int y, int player, int pieces);
    string finishMovePiece(vector<int> pointsClicked);
    void startAnimation(vector<int> pointsClicked, string type);
    bool posIsOutter(int xFinal, int yFinal);
    vector<vector< Stack * > > getCurrentState();
    void update();
	Board();
	void draw();
    CGFappearance * app1;
    CGFappearance * app2;
    CGFappearance * app3;
    CGFappearance * temp1;
    CGFappearance * temp3;
    CGFappearance * temp2;
    void showBoard();
	virtual ~Board();
};

#endif
