#ifndef __CGFExample__XMLParser__
#define __CGFExample__XMLParser__

#include <stdio.h>
#include "tinyxml.h"
#include <string.h>
#include "CGFshader.h"
#include <strings.h>
#include "Globals.h"
#include "Camera.h"
#include "Light.h"

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
    
protected:
    
    TiXmlDocument* doc;
    TiXmlElement* anfElement;
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* lightsElement;

    Globals * global;
    vector<Camera*> cameras;
    vector<Light*> lights;
    
};

#endif /* defined(__CGFExample__XMLParser__) */
