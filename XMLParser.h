//
//  XMLParser.h
//  CGFExample
//
//  Created by Ricardo Loureiro on 23/09/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__XMLParser__
#define __CGFExample__XMLParser__

#include <stdio.h>

#include "tinyxml.h"
#include "CGFscene.h"
#include <string.h>
#include "CGFshader.h"

class XMLParser
{
public:
    XMLParser(char *filename);
    ~XMLParser();
    static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    bool checkTrue(char *currentString) {
        const char *s2 = "true";
        if(!(strcasecmp(currentString,s2) == 0)){
            return false;
        }
        return true;
    }
    
    // Getters
    char* getDrawingMode(){return drawingMode;}
    char* getShading(){return shading;}
    float* getBackgroundColor(){return backgroundColor;}
    
    char* getFace(){return face;}
    char* getOrder(){return order;}
    
    //first is "doublesided", then "local" and finally "enabled"
    bool* getLightningProperties(){bool lightTemp[3];
        lightTemp[0]=doublesided;lightTemp[1]=local;lightTemp[2]=enabled;
        return lightTemp;
    }
    float* getAmbientLight(){return ambient;}
    
protected:
    
    TiXmlDocument* doc;
    TiXmlElement* globalsElement;
    
    /** GLOBAL PROPERITES **/
    // drawing properties
    char* drawingMode;
    char* shading;
    float backgroundColor[4];
    
    // culling properties
    char* face;
    char* order;
    
    // lighting properties
    bool doublesided;
    bool local;
    bool enabled;
    float ambient[4];
    
    
    
    // random stuff to erase
    
    TiXmlElement* matsElement;
    TiXmlElement* textsElement;
    TiXmlElement* leavesElement;
    TiXmlElement* nodesElement;
    TiXmlElement* graphElement;
};

#endif /* defined(__CGFExample__XMLParser__) */
