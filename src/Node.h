
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
    
public:
    
};
#endif /* defined(__CGFExample__Node__) */
