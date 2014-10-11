
#ifndef __CGFExample__Node__
#define __CGFExample__Node__

#include <stdio.h>
#include <vector>
#include "Primitive.h"
#include "Transform.h"

using namespace std;

class Node {
private:
    vector<Primitive *> primitives;
    vector<Transform *> transforms;
    char * appearenceRef;
    vector<Node *> descendents;
    float transformMatrix[4][4];
    char * id;
    bool processed;
    
public:
    Node(){processed = false;}

    void addPrimitive(Primitive *currentPrimitive){
    	this->primitives.push_back(currentPrimitive);
    }
    
    void addTransform(Transform * currentTransform){
    	this->transforms.push_back(currentTransform);
    }

    void setAppearence(char * appearenceName){
    	this->appearenceRef = appearenceName;
    }

    void setDescendents(Node * descendent){
    	this->descendents.push_back(descendent);
    }

	void setAppearenceRef(char* appearenceRef) {
		this->appearenceRef = appearenceRef;
	}

	char* getAppearenceRef() const {
		return appearenceRef;
	}

	vector<Node*>& getDescendents() {
		return descendents;
	}

	const vector<Primitive*>& getPrimitives() const {
		return primitives;
	}

	const vector<Transform*>& getTransforms() const {
		return transforms;
	}

	char* getId() const {
		return id;
	}

	void setId(char* id) {
		this->id = id;
	}

	void setMatrix(){

		glLoadIdentity();

		for(int i = 0; i < transforms.size(); i++) {

			cout << "transform type: " << transforms[i]->getType() << endl;

			if(strcmp(transforms[i]->getType(), "translate") == 0) {
				glTranslated(transforms[i]->getTo()[0],transforms[i]->getTo()[1],transforms[i]->getTo()[2]);
			}
			else if(strcmp(transforms[i]->getType(), "rotate") == 0) {
				cout << "ROTATE " << transforms[i]->getAxis() << " " << transforms[i]->getAngle() << endl;
				if(transforms[i]->getAxis() == 'x') {
					glRotated(transforms[i]->getAngle(),1,0,0);
				}
				else if(transforms[i]->getAxis() == 'y') {
					glRotated(transforms[i]->getAngle(),0,1,0);
				}
				else if(transforms[i]->getAxis() == 'z') {
					glRotated(transforms[i]->getAngle(),0,0,1);
				}
			}
			else if(strcmp(transforms[i]->getType(), "scale") == 0) {
				glScaled(transforms[i]->getFactor()[0],transforms[i]->getFactor()[1],transforms[i]->getFactor()[2]);
			}
		}

		glGetFloatv(GL_MODELVIEW_MATRIX, &transformMatrix[0][0]);

	}

	float* getTransformMatrix() {
		return &transformMatrix[0][0];
	}

	bool isProcessed() const {
		return processed;
	}

	void setProcessed(bool processed) {
		this->processed = processed;
	}
};
#endif /* defined(__CGFExample__Node__) */
