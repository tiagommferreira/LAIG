#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "CGFscene.h"
#include "XMLParser.h"
#include "CGFshader.h"
#include "CGFappearance.h"

class XMLScene : public CGFscene
{
public:
    void init();
    void display();
    void update(unsigned long t);
  
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:
    XMLParser* parser;
    CGFshader* shader;
    void drawGraph();
    void drawNode(Node*, Node*, float*);
    void drawRectangle(string,float[2],float[2]);
    void drawTriangle(string,float[3],float[3],float[3]);
    void drawCylinder(string,float,float,float,int,int);
    void drawSphere(string,float,int,int);
    void drawTorus(string,float,float,int,int);
};

#endif
