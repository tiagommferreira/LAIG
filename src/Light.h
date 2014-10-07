#ifndef __CGFExample__Light__
#define __CGFExample__Light__

#include <stdio.h>

class Light{
private:
	char* idLight;
	char* type;
	char* enabled;
	char* marker;
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

	char* getID();
	char* getType();
	char* getEnabled();
	char* getMarker();
	float* getPosition();
	float* getAmbientComponent();
	float* getDiffuseComponent();
	float* getSpecularComponent();

};

#endif /* defined(__CGFExample__Light__) */
