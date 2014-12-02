
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
    
	for(int i=0;i<5;i++){
		vector<Section *> sectionRow;
		for(int j=0;j<7;j++){
			sectionRow.push_back(new Section(i,j));
		}
		this->board.push_back(sectionRow);
	}
}

Board::~Board() {
}

void Board::draw(){
    int rows=0;
    int cols=0;
	for(unsigned int i=0;i<board.size();i++){
		for(unsigned int j=0;j<board[i].size();j++){
            if(j==0 || i==0 || i==4 || j==6){
                app1->apply();
            }else{
                app2->apply();
            }
            glLoadName(rows);
            glPushName(cols);
			board[i][j]->draw();
            glPopName();
			glTranslated(1,0,0);
            rows++;
		}
        rows=0;
        cols++;
		glTranslated(-7,1,0);
	}
}

