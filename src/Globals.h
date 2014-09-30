
#ifndef __CGFExample__Globals__
#define __CGFExample__Globals__

#include <stdio.h>
#include <string.h>
#include <iostream>


class Globals{
public:
    Globals(){}
    
    char* toLowerCase(char* string){
        int i;
        for(i=0;string[i];i++){
            string[i]=tolower(string[i]);
        }
        return string;
    }
    
    
    // Getters
    char* getDrawingMode(){return drawingMode;}
    char* getShading(){return shading;}
    float* getBackgroundColor(){return backgroundColor;}
    char* getFace(){return face;}
    char* getOrder(){return order;}
    
    //first is "doublesided", then "local" and finally "enabled"
    char* getDoublesided(){return doublesided;}
    char* getLocal(){return local;}
    char* getEnabled(){return enabled;}
    float* getAmbientLight(){return ambient;}
    
    // Setters
    void setBackgroundColor(char *color) {
        sscanf(color, "%f %f %f %f",&backgroundColor[0],&backgroundColor[1],
               &backgroundColor[2],&backgroundColor[3]);
    }
    
    void setDrawingMode (char *drawingMode) {
        this->drawingMode = toLowerCase(drawingMode);
    }
    
    void setShading (char *shading) {
        this->shading = toLowerCase(shading);
    }
    
    void setOrder( char * order){
        this->order = toLowerCase(order);
    }
    
    void setFace (char *face){
        this->face = toLowerCase(face);
    }
    
    void setDoublesided (char *doubles){
        this->doublesided = toLowerCase(doubles);
    }
    
    void setLocal (char *local){
        this->local = toLowerCase(local);
    }
    
    void setEnable (char *enable){
        this->enabled = toLowerCase(enable);
    }
    
    void setAmbient(char *ambient){
        sscanf(ambient, "%f %f %f %f",&this->ambient[0],&this->ambient[1],
               &this->ambient[2],&this->ambient[3]);
    }

protected:
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
};

#endif /* defined(__CGFExample__Globals__) */
