#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <vector>

using namespace std;

class Animation {
private:
	string id;
	float time;
	bool over;
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

	bool isOver() const {
		return over;
	}

	void setOver(bool over) {
		this->over = over;
	}
};

class LinearAnimation: public Animation {
private:
	vector< vector<float> > controlPoints;
	vector<float> deltaX;
	vector<float>deltaY;
	vector<float>deltaZ;
	float currentX,currentY,currentZ;
	vector<float> distances;
	int currentAnimState;
public:
	LinearAnimation(string id, float time, vector< vector<float> > controlPoints, int type):
		Animation(id, time, type) {
		this->controlPoints = controlPoints;
	}

	void addDeltaX(float deltaX){
		this->deltaX.push_back(deltaX);
	}

	void addDeltaZ(float deltaZ){
		this->deltaZ.push_back(deltaZ);
	}

	void addDeltaY(float deltaY){
		this->deltaY.push_back(deltaY);
	}
	void addDistance(float dist){
		this->distances.push_back(dist);
	}

	vector< vector<float> > getControlPoints(){
		return controlPoints;
	}

	void setControlPoints(const vector<vector<float> >& controlPoints) {
		this->controlPoints = controlPoints;
	}

	int getCurrentAnimState() const {
		return currentAnimState;
	}

	void setCurrentAnimState(int currentAnimState) {
		this->currentAnimState = currentAnimState;
	}

	float getCurrentX() const {
		return currentX;
	}

	void setCurrentX(float currentX) {
		this->currentX = currentX;
	}

	float getCurrentY() const {
		return currentY;
	}

	void setCurrentY(float currentY) {
		this->currentY = currentY;
	}

	float getCurrentZ() const {
		return currentZ;
	}

	void setCurrentZ(float currentZ) {
		this->currentZ = currentZ;
	}

	const vector<float>& getDeltaX() const {
		return deltaX;
	}

	void setDeltaX(const vector<float>& deltaX) {
		this->deltaX = deltaX;
	}

	const vector<float>& getDeltaY() const {
		return deltaY;
	}

	void setDeltaY(const vector<float>& deltaY) {
		this->deltaY = deltaY;
	}

	const vector<float>& getDeltaZ() const {
		return deltaZ;
	}

	void setDeltaZ(const vector<float>& deltaZ) {
		this->deltaZ = deltaZ;
	}

	const vector<float>& getDistances() const {
		return distances;
	}

	void setDistances(const vector<float>& distances) {
		this->distances = distances;
	}
};

class CircularAnimation: public Animation {
private:
	float currentAngle;
	float deltaAngle;
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

	float getCurrentAngle() const {
		return currentAngle;
	}

	void setCurrentAngle(float currentAngle) {
		this->currentAngle = currentAngle;
	}

	float getDeltaAngle() const {
		return deltaAngle;
	}

	void setDeltaAngle(float deltaAngle) {
		this->deltaAngle = deltaAngle;
	}
};

#endif
