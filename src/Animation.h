#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <vector>

using namespace std;

class Animation {
private:
	int id;
	float time;
public:
	Animation(int id, float time){
		this->id = id;
		this->time = time;
	};

	float getTime() {
		return time;
	}

	int getId() {
		return id;
	}

};


class LinearAnimation: public Animation {
private:
	vector< vector<float> > controlPoints;
public:
	LinearAnimation(int id, float time, vector< vector<float> > controlPoints): Animation(id, time) {
		this->controlPoints = controlPoints;
	}
	vector< vector<float> > getControlPoints(){
		return controlPoints;
	}
};


class CircularAnimation: public Animation {
private:
	vector<float> center;
	float radious;
	float initAngle;
	float rotationAngle;
public:
	vector<float> getCenter() {
		return center;
	}

	float getRadious() {
		return radious;
	}

	float getInitAngle() {
		return initAngle;
	}

	float getRotationAngle() {
		return rotationAngle;
	}
};

#endif
