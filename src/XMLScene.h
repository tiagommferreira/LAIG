#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "CGFscene.h"
#include "XMLParser.h"
#include "CGFshader.h"
#include "UserInterface.h"
#include "PickInterface.h"
#include "CGFappearance.h"
#include "PlogSocket.h"
#include "Game.h"
#include "CGFapplication.h"
#include <time.h>
#include <vector>
#include <string.h>
#include "Board.h"

class XMLScene : public CGFscene
{
public:
    void init();
    void display();
    void update(unsigned long t);
    
    int sceneVar;
	~XMLScene();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    XMLParser* getParser() {
        return this->parser;
    }
    void gameView();
    void undoMove();
    void toggleLight(int lightId);
    void addCameras(char*);
    void addLights();
    void drawLights();
    void setNodesAppearances();
    void setCamera(char* camera){this->camera=camera;}
    void setDrawingType(char*);
    void setNodeChildApp(Node*);
    void clickPiece(int);
    void addPoint(int);
    void setCurrentAmbient(int);
    void swapPosition();
    bool checkBoardChanges(char*);
    void doPCMove();
    void updatePointsClicked(char*);
    string createPlayCommand();
    string createPCCommand();
    string createPieceCommand();
    void setvsPC(bool);
    bool getvsPC();
    void printMessage();
protected:
    int currentAnimationState;
    time_t lastAnimationTime;
    bool isFilmActive;
    bool finishAnimation;
    bool vsPc = false;
    
    PlogSocket *socket;
    Game* gameState;
    vector<int> pointsClicked;
    Board * board;
    vector<string> states;
    vector<vector<int> > pointsClickedOverTime;
    
    char * camera;
    vector<CGFlight*>lights;
    vector<CGFappearance*>appearances;
    XMLParser* parser;
    CGFshader* shader;
    bool fill = false;
    bool wire =  false;
    bool point = false;
};

#endif
