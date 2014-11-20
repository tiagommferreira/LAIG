#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "CGFscene.h"
#include "XMLParser.h"
#include "CGFshader.h"
#include "UserInterface.h"
#include "PickInterface.h"
#include "CGFappearance.h"
#include "CGFapplication.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...

#define BUFS	1024
#define NAMS	64


#include <vector>
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

	void connectToSocket();
	void send(char* buffer);
	void receive(char* answer);
	void quit();

protected:
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[BUFS];

	vector<int> pointsClicked;
	Board * board;
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
