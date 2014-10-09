
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
    
public:
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

	const vector<Node*>& getDescendents() const {
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

			cout << transforms[i]->getType() << endl;

			if(strcmp(transforms[i]->getType(), "translate") == 0) {

				cout << "TRANSLATE" << endl;
				cout << "X " << transforms[i]->getTo()[0] << endl;
				cout << "y " << transforms[i]->getTo()[1] << endl;
				cout << "z " << transforms[i]->getTo()[2] << endl;

				glTranslated(transforms[i]->getTo()[0],transforms[i]->getTo()[1],transforms[i]->getTo()[2]);
			}
		}

		glGetFloatv(GL_MODELVIEW_MATRIX, &transformMatrix[0][0]);

	}

	const float* getTransformMatrix() const {
		return &transformMatrix[0][0];
	}


};
#endif /* defined(__CGFExample__Node__) */
