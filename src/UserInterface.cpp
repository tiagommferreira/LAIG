#include "UserInterface.h"

UserInterface::UserInterface() {
    testVar=0;
}


void UserInterface::processKeyboard(unsigned char key, int x, int y) {
}

void UserInterface::initGUI() {
    generalPanel = addPanel((char*)"Main Panel");
    
    addColumnToPanel(generalPanel);
    lightPanel = addPanelToPanel(generalPanel,(char*)"Lights",1);
    for(int i=0;i<((XMLScene *) scene)->getParser()->getLights().size();i++){
        // fazer um check para se a luz tiver activa ficar logo com o check
        addCheckboxToPanel(lightPanel,(char*)"toggle light",0,i);
    }
    
    addColumnToPanel(generalPanel);
    drawMode = addPanelToPanel(generalPanel,(char*)"Set drawing texture",1);
    radio = addRadioGroupToPanel(drawMode,0,8);
    addRadioButtonToGroup(radio,(char*)"wired");
    addRadioButtonToGroup(radio,(char*)"normal");
    addRadioButtonToGroup(radio,(char*)"outra cena");
    
    addColumnToPanel(generalPanel);
    cameraPanel = addPanelToPanel(generalPanel,(char*) "Cameras",1);
    list = addListboxToPanel(cameraPanel,(char*)"",0,10);
    for(int i=0;i<((XMLScene *) scene)->getParser()->getCameras().size();i++){
        list->add_item(i+11,(char*)((XMLScene *) scene)->getParser()->getCameras()[i]->getId());
    }
}

void UserInterface::processGUI(GLUI_Control *ctrl) {
    if(ctrl->user_id>=0 && ctrl->user_id <= ((XMLScene *) scene)->getParser()->getLights().size()){
        cout << "light with the id of " << ctrl->user_id << " was toggled\n";
        //fazer uma função para activar ou desativar uma certa luz na XMLscene
    }else if(ctrl->user_id==8){
        cout << "Change of the drawing mode, current ->" << radio->get_int_val() << endl;
    }else if(ctrl->user_id>=9 && ctrl->user_id<((XMLScene *) scene)->getParser()->getCameras().size()+9) {
        cout << "Camera change, current camera->" << (list->get_int_val()) << endl;
    }else{
        cout << "dafuq\n" << endl;
    }
}

