
#include "Board.h"
using namespace std;

Board::Board() {
	for(int i=0;i<5;i++){
		vector<Section *> sectionRow;
		for(int j=0;j<7;j++){
			sectionRow.push_back(new Section(i,j));
		}
		this->board.push_back(sectionRow);
	}
	cout << board.size() << " #" << board[0].size() << endl;
}


Board::~Board() {
	// TODO Auto-generated destructor stub
}


void Board::draw(){

	for(unsigned int i=0;i<board.size();i++){
		for(unsigned int j=0;j<board[i].size();j++){
			board[i][j]->draw();
			glTranslated(2,0,0);
		}
		glTranslated(-14,2,0);
	}
}

