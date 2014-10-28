#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <vector>

using namespace std;

class Animation {
private:
	string id;
	float time;
public:
	Animation(string id, float time){
		this->id = id;
		this->time = time;
	};

	float getTime() {
		return time;
	}

	string getId() {
		return id;
	}

};


class LinearAnimation: public Animation {
private:
	vector< vector<float> > controlPoints;
public:
	LinearAnimation(string id, float time, vector< vector<float> > controlPoints): Animation(id, time) {
		this->controlPoints = controlPoints;
	}
	vector< vector<float> > getControlPoints(){
		return controlPoints;
	}
};


class CircularAnimation: public Animation {
private:
	vector<float> center;
	float radius;
	float initAngle;
	float rotationAngle;
public:
	CircularAnimation(string id, float time, vector<float> center, float radius, float initAngle, float rotationAngle): Animation(id,time) {
		this->center = center;
		this->radius = radius;
		this->initAngle = initAngle;
		this->rotationAngle = rotationAngle;
	}

	vector<float> getCenter() {
		return center;
	}

	float getRadious() {
		return radius;
	}

	float getInitAngle() {
		return initAngle;
	}

	float getRotationAngle() {
		return rotationAngle;
	}
};

#endif
