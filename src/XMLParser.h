#ifndef __CGFExample__XMLParser__
#define __CGFExample__XMLParser__

#include <stdio.h>
#include <string.h>
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"
#include "Light.h"
#include "Node.h"
#include "Transform.h"
#include "Texture.h"
#include "Animation.h"
#include "Appearance.h"
#include "tinyxml.h"
#include "Plane.h"
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
    vector<Appearance*> getAppearances(){return this->appearances;}
    vector<Texture*> getTextures(){return this->textures;}
    map<char*,Node*> getGraph(){return this->graph;}
    char* getRootid(){return rootid;}
    void setEmptyNodes();
    void setChildrenDisplayLists();
    Plane * getPlane(){
    	return this->plane;
    }
    
protected:
    
    TiXmlDocument* doc;
    TiXmlElement* anfElement;
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* lightsElement;
    TiXmlElement* graphElement;
    TiXmlElement* appearancesElement;
    TiXmlElement* texturesElement;
    TiXmlElement* animationsElement;
    
    Globals * global;
    vector<Camera*> cameras;
    vector<Light*> lights;
    vector<Appearance*> appearances;
    vector<Texture*> textures;
    vector<Animation*> animations;
    map<char*,Node*> graph;
    Plane * plane;
    char* rootid;
    
};

#endif /* defined(__CGFExample__XMLParser__) */
