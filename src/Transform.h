
#ifndef __CGFExample__Transform__
#define __CGFExample__Transform__

#include <stdio.h>

class Transform {
private:
    
    char * type;
    float to[3];
    char axis;
    float angle;
    float factor[3];
public:
    Transform(){}
    void setType(char * type){this->type=type;}
    void setTo(char * to){sscanf(to, "%f %f %f",&this->to[0],&this->to[1],&this->to[2]);}
    void setAxis(char axis) {this->axis=axis;}
    void setAngle(float angle){this->angle=angle;}
    void setFactor(char * factor){sscanf(factor, "%f %f %f",&this->factor[0],&this->factor[1],&this->factor[2]);}
};

#endif /* defined(__CGFExample__Transform__) */
