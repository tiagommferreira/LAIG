#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "CGFscene.h"
#include "XMLParser.h"
#include "CGFshader.h"
#include "UserInterface.h"
#include "CGFappearance.h"
#include "CGFapplication.h"
#include <vector>

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
    
    void toggleLight(int lightId){
        if(strcmp(parser->getLights()[lightId]->getEnabled(),"true")==0){
            parser->getLights()[lightId]->setEnabled((char*)"false");
            cout << "now is false" << endl;
            lights[lightId]->disable();
            lights[lightId]->update();
        } else if(strcmp(parser->getLights()[lightId]->getEnabled(),"false")==0){
           parser->getLights()[lightId]->setEnabled((char*)"true");
            cout << "now is true" << endl;
            lights[lightId]->enable();
            lights[lightId]->update();
        }
    }
    
    
    void addLights();
    void drawLights();
    void setNodesAppearances();
    
protected:
    vector<CGFlight*>lights;
    vector<CGFappearance*>appearances;
    XMLParser* parser;
    CGFshader* shader;
};

#endif
