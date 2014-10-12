
#ifndef __CGFExample__Camera__
#define __CGFExample__Camera__

#include <stdio.h>

class Camera{
public:
    Camera(){}
    void setId(char *i){this->idCamera=i;}
    void setOrthoFar(float i){this->orthoFar=i;}
    void setOrthoNear(float i){this->orthoNear=i;}
    void setOrthoLeft(float i){this->orthoLeft=i;}
    void setOrthoBottom(float i){this->orthoBottom=i;}
    void setOrthoTop(float i){this->orthoTop=i;}
    void setOrthoRight(float i){this->orthoRight=i;}
    void setOrthoDirection(char i){this->orthoDirection=i;}
    // ______
    void setNearPerspec(float i){this->perspecNear=i;}
    void setFarPerspec(float i){this->perspecFar=i;}
    void setAnglePerspec(float i){this->perspecAngle=i;}
    void setPerspPos(char *i){
        sscanf(i, "%f %f %f",&perspecPos[0],&perspecPos[1],
               &perspecPos[2]);
    }
    void setPerspTarget(char *i){
        sscanf(i, "%f %f %f",&perspecTarget[0],&perspecTarget[1],
               &perspecTarget[2]);
    }
    
    
    float getOrthoLeft() {
        return orthoLeft;
    }
    
    float getOrthoRight() {
        return orthoRight;
    }
    
    float getOrthoTop() {
        return orthoTop;
    }
    
    float getOrthoBottom() {
        return orthoBottom;
    }
    
    float getOrthoNear() {
        return orthoNear;
    }
    
    float getOrthoFar() {
        return orthoFar;
    }
    
    char getOrthoDirection() {
        return orthoDirection;
    }
    
    char * getInitial(){
        return initialId;
    }
    
    void setInitial(char* initial){
        this->initialId = initial;
    }

    char * getId(){
        return this->idCamera;
    }
    
    int getType(){
        return type;
        
    }
    
    float getPerspecNear(){
        return this->perspecNear;
    }
    
    float getPerspecFar(){
        return this->perspecFar;
    }
    
    float getPerspecAngle(){
        return this->perspecAngle;
    }
    float * getPerspecPos() {
        return this->perspecPos;
    }
    
    float * getPerspecTarget() {
        return this->perspecTarget;
    }
    
    void setType(int i) {
        this->type = i;
    }
    
private:
    int type; // 0->perspectiva 1->ortogonal
    char * initialId;
    char *idCamera;
    
    //ortho properties
    char orthoDirection;
    float orthoNear, orthoFar, orthoLeft, orthoRight, orthoBottom, orthoTop;
    
    //perspective properties
    float perspecNear, perspecFar, perspecAngle;
    float perspecPos[3];
	float perspecTarget[3];
};


#endif /* defined(__CGFExample__Camera__) */
