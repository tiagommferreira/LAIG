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
        if(strcmp(((XMLScene *) scene)->getParser()->getLights()[i]->getEnabled(),"true")==0){
            addCheckboxToPanel(lightPanel,(char*)((XMLScene *) scene)->getParser()->getLights()[i]->getID(),0,i)->set_int_val(1);
        }else{
            addCheckboxToPanel(lightPanel,(char*)((XMLScene *) scene)->getParser()->getLights()[i]->getID(),0,i);
        }
    }
    
    addColumnToPanel(generalPanel);
    drawMode = addPanelToPanel(generalPanel,(char*)"Set drawing texture",1);
    radio = addRadioGroupToPanel(drawMode,0,8);
    addRadioButtonToGroup(radio,(char*)"fill");
    addRadioButtonToGroup(radio,(char*)"point");
    addRadioButtonToGroup(radio,(char*)"line");
    
    addColumnToPanel(generalPanel);
    cameraPanel = addPanelToPanel(generalPanel,(char*) "Cameras",1);
    list = addListboxToPanel(cameraPanel,(char*)"",0,9);
    for(int i=0;i<((XMLScene *) scene)->getParser()->getCameras().size();i++){
        list->add_item(i,(char*)((XMLScene *) scene)->getParser()->getCameras()[i]->getId());
    }
}

void UserInterface::processGUI(GLUI_Control *ctrl) {
    if(ctrl->user_id>=0 && ctrl->user_id <= ((XMLScene *) scene)->getParser()->getLights().size()){
        cout << "light with the id of " << ctrl->user_id << " was toggled\n";
        ((XMLScene *) scene)->toggleLight(ctrl->user_id);
        //fazer uma função para activar ou desativar uma certa luz na XMLscene
    }else if(ctrl->user_id==8){
        cout << "Change of the drawing mode, current ->" << radio->get_int_val() << endl;
        switch (radio->get_int_val()) {
            case 0:{
                ((XMLScene *) scene)->setDrawingType((char*)"fill");
            }
                break;
            case 1:{
                ((XMLScene *) scene)->setDrawingType((char*)"point");
            }
                break;
            case 2: {
                ((XMLScene *) scene)->setDrawingType((char*)"line");
            }
                break;
            default:
                break;
        }
    }else if(ctrl->user_id==9) {
        cout << "Camera change, current camera->" << (list->get_int_val()) << endl;
        ((XMLScene *) scene)->setCamera((char*)((XMLScene *) scene)->getParser()->getCameras()[list->get_int_val()]->getId());
    }else{
        cout << "dafuq\n" << endl;
    }
}

