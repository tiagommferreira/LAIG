#ifndef __CGFExample__XMLParser__
#define __CGFExample__XMLParser__

#include <stdio.h>
#include "tinyxml.h"
#include <string.h>
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"
#include "Light.h"
#include "Node.h"
#include "Transform.h"
#include <map>

class XMLParser
{
public:
    XMLParser();
    ~XMLParser();
    
    static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    bool checkTrue(char *currentString) {
        const char *s2 = "true";
        if(!(strcmp (currentString,s2) == 0)){
            return false;
        }
        return true;
    }
    Globals * getGlobals(){return this->global;}
    vector<Camera*> getCameras(){return this->cameras;}
    vector<Light*> getLights(){return this->lights;}
    map<char*,Node*> getGraph(){return this->graph;}
    char* getRootid(){return rootid;}
    void setEmptyNodes();

protected:
    
    TiXmlDocument* doc;
    TiXmlElement* anfElement;
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* lightsElement;
    TiXmlElement* graphElement;
    

    Globals * global;
    vector<Camera*> cameras;
    vector<Light*> lights;
    map<char*,Node*> graph;
    char* rootid;
    
};

#endif /* defined(__CGFExample__XMLParser__) */
