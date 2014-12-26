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
    void swapPosition();
    bool checkBoardChanges(char*);
    string createPlayCommand();
    string createPieceCommand();

protected:
    
    PlogSocket *socket;
    Game* gameState;
    vector<int> pointsClicked;
    Board * board;
    vector<Board*> boards;
    
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
