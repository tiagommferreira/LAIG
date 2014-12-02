
#ifndef __CGFExample__PickInterface__
#define __CGFExample__PickInterface__

#include <stdio.h>
#include "CGFinterface.h"
using namespace std;

class PickInterface: public CGFinterface {
public:
    virtual void processMouse(int button, int state, int x, int y);
    void performPicking(int x, int y);
    void processHits(GLint hits, GLuint buffer[]);
};

#endif /* defined(__CGFExample__PickInterface__) */
