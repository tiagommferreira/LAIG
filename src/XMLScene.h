#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "CGFscene.h"
#include "XMLParser.h"
#include "CGFshader.h"
#include "UserInterface.h"
#include "CGFappearance.h"
#include "CGFapplication.h"

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
    
protected:
    XMLParser* parser;
    CGFshader* shader;
};

#endif
