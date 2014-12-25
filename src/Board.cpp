
#include "Board.h"
using namespace std;

Board::Board():Primitive((char*)"board") {
    
    float amb[4] = {0.4,0.4,0.4,1};
    float dif[4] = {0.5,0.5,0.5,1};
    float spec[4] = {1,1,1,1};
    app1 = new CGFappearance(amb,dif,spec,20);
    app2 = new CGFappearance(amb,dif,spec,20);
    CGFtexture * currentTexture = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/azul.jpg");
    CGFtexture * currentTexture2 = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/azul_claro.jpg");
    
    app1->setTexture(currentTexture);
    app2->setTexture(currentTexture2);
    
    this->section = new Section();
    
    /**
     * Initiliazing the board game
     */
    vector<Stack * > row;
    row.push_back(new Stack(0,0));row.push_back(new Stack(0,0));row.push_back(new Stack(0,0));row.push_back(new Stack(0,0));
    row.push_back(new Stack(0,0));row.push_back(new Stack(0,0));row.push_back(new Stack(0,0));
    vector<Stack * > scdRow;
    scdRow.push_back(new Stack(0,0));scdRow.push_back(new Stack(3,1));scdRow.push_back(new Stack(3,2));scdRow.push_back(new Stack(3,1));
    scdRow.push_back(new Stack(3,2));scdRow.push_back(new Stack(3,1)); scdRow.push_back(new Stack(0,0));
    vector<Stack * > trdRow;
    trdRow.push_back(new Stack(0,0));trdRow.push_back(new Stack(3,2));trdRow.push_back(new Stack(3,1));trdRow.push_back(new Stack(0,0));
    trdRow.push_back(new Stack(3,2));trdRow.push_back(new Stack(3,1));trdRow.push_back(new Stack(0,0));
    vector<Stack * > fourthRow;
    fourthRow.push_back(new Stack(0,0));fourthRow.push_back(new Stack(3,2));fourthRow.push_back(new Stack(3,1));
    fourthRow.push_back(new Stack(3,2));
    fourthRow.push_back(new Stack(3,1));fourthRow.push_back(new Stack(3,2));fourthRow.push_back(new Stack(0,0));
    vector<Stack * > fifthRow;
    fifthRow.push_back(new Stack(0,0));fifthRow.push_back(new Stack(0,0));fifthRow.push_back(new Stack(0,0));fifthRow.push_back(new Stack(0,0));
    fifthRow.push_back(new Stack(0,0));fifthRow.push_back(new Stack(0,0));fifthRow.push_back(new Stack(0,0));
    
    this->currentState.push_back(row);
    this->currentState.push_back(scdRow);
    this->currentState.push_back(trdRow);
    this->currentState.push_back(fourthRow);
    this->currentState.push_back(fifthRow);
    
    for(int i=0;i<currentState.size();i++){
        for(int j=0;j<currentState[i].size();j++){
            cout << currentState[i][j]->getNumberOfPieces() << "," << currentState[i][j]->getPlayerNumber() << " | ";
        }
        cout << endl;
    }
    temp1 = new CGFappearance(amb,dif,spec,20);
    temp2 = new CGFappearance(amb,dif,spec,20);

    CGFtexture * txt1 = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/images-600x331.jpg");
    CGFtexture * txt2 = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/images.jpg");
    
    temp1->setTexture(txt1);
    temp2->setTexture(txt2);
}

Board::~Board() {
}

void Board::draw(){
    int row=0;
    int col=0;
    
    for(unsigned int i=0;i<5;i++){
		for(unsigned int j=0;j<7;j++){
            if(j==0 || i==0 || i==4 || j==6){
                app1->apply();
            }else{
                app2->apply();
            }
            glLoadName(row);
            glPushName(col);
			this->section->draw();
            if(currentState[i][j]->getPlayerNumber()==1){
                temp1->apply();
            }else {
                temp2->apply();
            }
            currentState[i][j]->draw();
            glPopName();
			glTranslated(1,0,0);
            col++;
		}
        col=0;
        row++;
		glTranslated(-7,-1,0);
	}
}

void Board::showBoard() {
    for(unsigned int i=0;i<5;i++){
        for(unsigned int j=0;j<7;j++) {
            cout << currentState[i][j]->getNumberOfPieces() << "," << currentState[i][j]->getPlayerNumber() << " |";
         }
        cout << endl;
    }
}

vector<vector< Stack * > > Board::getCurrentState() {
    return this->currentState;
}

void Board::updateBoard(char * board) {
    string updatedBoard(board);
    
    string delimiter = "]";
    string delimiter2= ",";
    vector<string> rows;
    size_t pos=0;
    while((pos = updatedBoard.find(delimiter)) != string::npos) {
        rows.push_back(updatedBoard.substr(0,pos));
        updatedBoard.erase(0,pos+delimiter.length());
    }
    for(int i=0;i<rows.size();i++){
        rows[i].erase(0,2);
    }
    
    vector<vector<string> > separatedBoard;
    for(int i=0;i<rows.size()-1;i++){
        pos = 0;
        vector<string> currentRow;
        while((pos = rows[i].find(delimiter2)) != string::npos) {
            currentRow.push_back(rows[i].substr(0,pos));
            rows[i].erase(0,pos+delimiter2.length());
        }
        currentRow.push_back(rows[i]);
        separatedBoard.push_back(currentRow);
        currentRow.clear();
    }
    
    for(int i = 0; i<separatedBoard.size(); i++) {
        for(int j = 0; j<separatedBoard[i].size();j++) {
            int playerNumber = stoi(separatedBoard[i][j]) /10;
            int pieceNumber = stoi(separatedBoard[i][j])%10;
            if(pieceNumber==9){
                currentState[i][j]->setNumberOfPieces(0);
                currentState[i][j]->setPlayer(0);
            }
            else {
                currentState[i][j]->setNumberOfPieces(pieceNumber);
                currentState[i][j]->setPlayer(playerNumber);
            }
        }
    }
}

string Board::boardToString() {
    stringstream board;
    board << "[";
    for(int i = 0; i<currentState.size(); i++) {
        board << "[";
        for(int j = 0; j<currentState[i].size();j++) {
            if(currentState[i][j]->getNumberOfPieces()==0) {
                board << "99";
            }else {
                board << currentState[i][j]->getPlayerNumber() << currentState[i][j]->getNumberOfPieces();
            }
            if(j<6){
                board << ",";
            }
        }
        
        board << "]";
        if(i<4){
            board << ",";
        }
    }
    board << "]";
    
    return board.str();
}


