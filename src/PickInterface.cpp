#include "PickInterface.h"
#include "XMLScene.h"
#include "CGFapplication.h"

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];


void PickInterface::processMouse(int button, int state, int x, int y)
{
    CGFinterface::processMouse(button,state, x, y);
    
    // do picking on mouse press (GLUT_DOWN)
    // this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        performPicking(x,y);
}

void PickInterface::performPicking(int x, int y)
{
    // Sets the buffer to be used for selection and activate selection mode
    glSelectBuffer (BUFSIZE, selectBuf);
    glRenderMode(GL_SELECT);
    
    // Initialize the picking name stack
    glInitNames();
    
    // The process of picking manipulates the projection matrix
    // so we will be activating, saving and manipulating it
    glMatrixMode(GL_PROJECTION);
    
    //store current projmatrix to restore easily in the end with a pop
    glPushMatrix ();
    
    //get the actual projection matrix values on an array of our own to multiply with pick matrix later
    GLfloat projmat[16];
    glGetFloatv(GL_PROJECTION_MATRIX,projmat);
    
    // reset projection matrix
    glLoadIdentity();
    
    // get current viewport and use it as reference for
    // setting a small picking window of 5x5 pixels around mouse coordinates for picking
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    // this is multiplied in the projection matrix
    gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);
    
    // multiply the projection matrix stored in our array to ensure same conditions as in normal render
    glMultMatrixf(projmat);
    
    // force scene drawing under this mode
    // only the names of objects that fall in the 5x5 window will actually be stored in the buffer
    ((XMLScene *) scene)->display();
    
    // restore original projection matrix
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    
    glFlush();
    
    // revert to render mode, get the picking results and process them
    GLint hits;
    hits = glRenderMode(GL_RENDER);
    processHits(hits, selectBuf);
}

void PickInterface::processHits (GLint hits, GLuint buffer[])
{
    GLuint *ptr = buffer;
    GLuint mindepth = 0xFFFFFFFF;
    GLuint *selected=NULL;
    GLuint nselected;
    
    // iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
    for (int i=0;i<hits;i++) {
        int num = *ptr; ptr++;
        GLuint z1 = *ptr; ptr++;
        ptr++;
        if (z1 < mindepth && num>0) {
            mindepth = z1;
            selected = ptr;
            nselected=num;
        }
        for (int j=0; j < num; j++)
            ptr++;
    }
    
    // if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
    if (selected!=NULL)
    {
        // this should be replaced by code handling the picked object's ID's (stored in "selected"),
        // possibly invoking a method on the scene class and passing "selected" and "nselected"
        for (int i=0; i<nselected; i++){
            if(nselected==2)
                ((XMLScene *)scene)->addPoint(selected[i]);
        }
    }
    else
        printf("Please select a piece\n");
}

void PickInterface::initGUI() {
	generalPanel = addPanel((char*)"Opcoes de Jogo");
	addButtonToPanel(generalPanel, (char*)"Filme de Jogo",1);
	addButtonToPanel(generalPanel, (char*)"Voltar atras",2);

	addColumn();

	gameTypePanel = addPanel((char*)"Tipo de Jogo");
	radio = addRadioGroupToPanel(gameTypePanel,0,3);
	addRadioButtonToGroup(radio,(char*)"1vs1")->set_int_val(1);
	addRadioButtonToGroup(radio,(char*)"1vsPC");
    
    addColumn();
    
    ambientList = addListboxToPanel(generalPanel,(char*)"Ambiente de Jogo",0,4);
    ambientList->add_item(1, (char*)"Madeira");
    ambientList->add_item(2, (char*)"Vidro");
    ambientList->add_item(3, (char*)"Metal");
}

void PickInterface::processGUI(GLUI_Control *ctrl) {
	switch (ctrl->user_id) {
	case 1:
	{
		cout << "Filme de jogo\n";
		((XMLScene*)scene)->gameView();
	}
	break;
	case 2:
	{
		((XMLScene*)scene)->undoMove();
		cout << "Voltar atrás\n";
	}
	break;
	case 3:
		switch (radio->get_int_val()) {
		case 0:{
			((XMLScene *) scene)->setvsPC(false);
		}
		break;
		case 1:{
			((XMLScene *) scene)->setvsPC(true);
		}
		break;
		default:
			break;
		}
    break;
        case 4: {
            cout << "Current Ambient #" << ambientList->get_int_val() << endl;
            ((XMLScene *)scene)->setCurrentAmbient(ambientList->get_int_val());
        }
            break;
        default:
           
        break;
	}
}

