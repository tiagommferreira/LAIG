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
    void drawRectangle(string,float[2],float[2]);
};

#endif
