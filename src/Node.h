
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
};
#endif /* defined(__CGFExample__Node__) */
