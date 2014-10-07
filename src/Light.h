#ifndef __CGFExample__Light__
#define __CGFExample__Light__

#include <stdio.h>

class Light{
private:
	char* idLight;
	char* type;
	char* enabled;
	char* marker;
    
    float target[3];
    float angle;
    float exponent;
    
	float pos[3];
	float ambientComponent[4];
	float diffuseComponent[4];
	float specularComponent[4];

public:
	Light(){}
	void setID(char* id);
	void setType(char* type);
	void setEnabled(char* enabled);
	void setMarker(char* marker);
	void setPosition(char* pos);
	void setAmbientComponent(char* ambient);
	void setDiffuseComponent(char* diffuse);
	void setSpecularComponent(char* specular);
    void setTarget(char * target);
    void setAngle(float angle);
    void setExponent(float exponent);

	char* getID();
	char* getType();
	char* getEnabled();
	char* getMarker();
	float* getPosition();
	float* getAmbientComponent();
	float* getDiffuseComponent();
	float* getSpecularComponent();
    float* getTarget();
    float getAngle();
    float getExponent();

};

#endif /* defined(__CGFExample__Light__) */
