
#ifndef __CGFExample__UserInterface__
#define __CGFExample__UserInterface__

#include <stdio.h>
#include "CGFinterface.h"
#include "XMLScene.h"

class UserInterface: public CGFinterface {
public:
    UserInterface();
    
    GLUI_Panel *generalPanel;
    GLUI_Panel *lightPanel;
    GLUI_Panel *drawMode;
    GLUI_Panel *cameraPanel;
    GLUI_Listbox * list;
    GLUI_RadioGroup* radio;
    
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
    virtual void processKeyboard(unsigned char key, int x, int y);
    int testVar;
};
#endif /* defined(__CGFExample__UserInterface__) */
