#ifndef __CGFExample__XMLParser__
#define __CGFExample__XMLParser__

#include <stdio.h>
#include "tinyxml.h"
#include <string.h>
#include "CGFshader.h"
#include <strings.h>

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
    
    char* toLowerCase(char* string){
        int i;
        for(i=0;string[i];i++){
            string[i]=tolower(string[i]);
        }
        return string;
    }
    
    // Getters
    char* getDrawingMode(){toLowerCase(drawingMode);return drawingMode;}
    char* getShading(){toLowerCase(shading);return shading;}
    float* getBackgroundColor(){return backgroundColor;}
    
    char* getFace(){toLowerCase(face);return face;}
    char* getOrder(){toLowerCase(order);return order;}
    
    //first is "doublesided", then "local" and finally "enabled"
    char* getDoublesided(){toLowerCase(doublesided);return doublesided;}
    char* getLocal(){toLowerCase(local);return local;}
    char* getEnabled(){toLowerCase(enabled);return enabled;}
    float* getAmbientLight(){return ambient;}
    
protected:
    
    TiXmlDocument* doc;
    TiXmlElement* anfElement;
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* lightsElement;
    
    /** GLOBAL PROPERITES **/
    // drawing properties
    char* drawingMode;
    char* shading;
    float backgroundColor[4];
    
    // culling properties
    char* face;
    char* order;
    
    // lighting properties
    char* doublesided;
    char* local;
    char* enabled;
    float ambient[4];
    
    /* CAMERA PROPERTIES */
    //ortho properties
    char* orthoId;
    char orthoDirection;
    float orthoNear, orthoFar, orthoLeft, orthoRight, orthoBottom, orthoTop;
    
    //perspective properties
    char* perspecId;
    float perspecNear, perspecFar, perspecAngle;
    float* perspecPos, * perspecTarget;
    
    /* LIGHTS PROPERTIES */
    // Specific lights properties
    char * lightId, * lightType;
    bool * lightEnabled, * lightMarker;
    char * lightPos[3];
    char * lightAmbient[4];
    char * lightDiffuse[4];
    char * lightSpecular[4];
    
};

#endif /* defined(__CGFExample__XMLParser__) */
