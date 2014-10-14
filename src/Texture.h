#ifndef __CGFExample__Texture__
#define __CGFExample__Texture__

#include <stdio.h>

class Texture{
private:
	char* id;
	char* file;
	float texlenght_s;
	float texlenght_t;

public:
	Texture(){}

	char* getFile() const {
		return file;
	}

	void setFile(char* file) {
		this->file = file;
	}

	char* getId() const {
		return id;
	}

	void setId(char* id) {
		this->id = id;
	}

	float getTexlenghtS() const {
		return texlenght_s;
	}

	void setTexlenghtS(float texlenghtS) {
		texlenght_s = texlenghtS;
	}

	float getTexlenghtT() const {
		return texlenght_t;
	}

	void setTexlenghtT(float texlenghtT) {
		texlenght_t = texlenghtT;
	}
};

#endif /* defined(__CGFExample__Texture__) */
