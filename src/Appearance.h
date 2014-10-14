#ifndef __CGFExample__Appearance__
#define __CGFExample__Appearance__

#include <stdio.h>

class Appearance{
private:
	char* id;
	char* textureref;
	float shininess;
	float ambientComponent[4];
	float diffuseComponent[4];
	float specularComponent[4];

public:
	Appearance(){}

	const float* getAmbientComponent() const {
		return ambientComponent;
	}

	const float* getDiffuseComponent() const {
		return diffuseComponent;
	}

	char* getId() const {
		return id;
	}

	void setId(char* id) {
		this->id = id;
	}

	float getShininess() const {
		return shininess;
	}

	void setShininess(float shininess) {
		this->shininess = shininess;
	}

	const float* getSpecularComponent() const {
		return specularComponent;
	}

	char* getTextureref() const {
		return textureref;
	}

	void setTextureref(char* textureref) {
		this->textureref = textureref;
	}

	float* getAmbientComponent() {
		return ambientComponent;
	}
	float* getDiffuseComponent() {
		return diffuseComponent;
	}
	float* getSpecularComponent() {
		return specularComponent;
	}

	void setAmbientComponent(char* ambient) {
		sscanf(ambient, "%f %f %f %f",&this->ambientComponent[0],&this->ambientComponent[1],
	               &this->ambientComponent[2], &this->ambientComponent[3]);
	}
	void setDiffuseComponent(char* diffuse) {
		sscanf(diffuse, "%f %f %f %f",&this->diffuseComponent[0],&this->diffuseComponent[1],
	               &this->diffuseComponent[2], &this->diffuseComponent[3]);
	}
	void setSpecularComponent(char* specular) {
		sscanf(specular, "%f %f %f %f",&this->specularComponent[0],&this->specularComponent[1],
	               &this->specularComponent[2], &this->specularComponent[3]);
	}
};

#endif /* defined(__CGFExample__Appearance__) */
