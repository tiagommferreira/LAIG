#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <vector>

using namespace std;

class Animation {
private:
	string id;
	float time;
	int type;
public:
	Animation(string id, float time,int type){
		this->id = id;
		this->time = time;
		this->type = type; // 0 - circular , 1 - linear
	};

	float getTime() {
		return time;
	}

	string getId() {
		return id;
	}

	int getType() const {
		return type;
	}
};

class LinearAnimation: public Animation {
private:
	vector< vector<float> > controlPoints;
public:
	LinearAnimation(string id, float time, vector< vector<float> > controlPoints, int type):
		Animation(id, time, type) {
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
	CircularAnimation(string id, float time, vector<float> center,
			float radius, float initAngle, float rotationAngle, int type):
				Animation(id,time, type) {
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
