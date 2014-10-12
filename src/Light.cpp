#include "Light.h"


void Light::setID(char* id) {
	this->idLight = id;
}

void Light::setType(char* type) {
	this->type = type;
}

void Light::setEnabled(char *enabled) {
	this->enabled = enabled;
}
void Light::setMarker(char *marker) {
	this->marker = marker;
}
void Light::setPosition(char* pos) {
	sscanf(pos, "%f %f %f",&this->pos[0],&this->pos[1],
               &this->pos[2]);
}
void Light::setAmbientComponent(char* ambient) {
	sscanf(ambient, "%f %f %f %f",&this->ambientComponent[0],&this->ambientComponent[1],
               &this->ambientComponent[2], &this->ambientComponent[3]);
}
void Light::setDiffuseComponent(char* diffuse) {
	sscanf(diffuse, "%f %f %f %f",&this->diffuseComponent[0],&this->diffuseComponent[1],
               &this->diffuseComponent[2], &this->diffuseComponent[3]);
}
void Light::setSpecularComponent(char* specular) {
	sscanf(specular, "%f %f %f %f",&this->specularComponent[0],&this->specularComponent[1],
               &this->specularComponent[2], &this->specularComponent[3]);
}

char* Light::getID() {
	return idLight;
}
char* Light::getType() {
	return type;
}
char* Light::getEnabled() {
	return enabled;
}
char* Light::getMarker() {
	return marker;
}
float* Light::getPosition() {
	return pos;
}
float* Light::getAmbientComponent() {
	return ambientComponent;
}
float* Light::getDiffuseComponent() {
	return diffuseComponent;
}
float* Light::getSpecularComponent() {
	return specularComponent;
}

void Light::setTarget(char * target){
    sscanf(target, "%f %f %f",&this->target[0],&this->target[1],
           &this->target[2]);
}
void Light::setAngle(float angle) {
    this->angle = angle;
}
void Light::setExponent(float exponent){
    this->exponent = exponent;
}



