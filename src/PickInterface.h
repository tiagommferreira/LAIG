
#ifndef __CGFExample__PickInterface__
#define __CGFExample__PickInterface__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include "CGFinterface.h"
using namespace std;

class PickInterface: public CGFinterface {
private:
    GLUI_Panel *generalPanel;
public:
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
    virtual void processMouse(int button, int state, int x, int y);
    void performPicking(int x, int y);
    void processHits(GLint hits, GLuint buffer[]);
    void connectToSocket();

};

#endif /* defined(__CGFExample__PickInterface__) */
