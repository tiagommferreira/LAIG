#include "XMLScene.h"
#include "XMLParser.h"
#include <string.h>
#include <iostream>

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val) {
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();
	return child;
}

void XMLScene::init() {
    /** Parses the information from xml to c++ **/
    parser = new XMLParser();
    shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

    /* GLOBALS */
    
    // CULLING PROPERTIES
    if((strcmp (parser->getOrder(),"cw")==0)){
        glFrontFace(GL_CW);
    }else {
        glFrontFace(GL_CCW);
    }
    
    // also has the possibility to be none
    if((strcmp(parser->getFace(),"front")==0)){
        glCullFace(GL_FRONT);
    }else if((strcmp (parser->getFace(),"back")==0)){
        glCullFace(GL_BACK);
    }
    
    
    //LIGHTING PROPERTIES
    if((strcmp (parser->getEnabled(),"true")==0)){
        glEnable(GL_LIGHTING);
    }
    if((strcmp (parser->getLocal(),"true")==0)){
        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    }
    if((strcmp (parser->getDoublesided(),"true")==0)){
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    }
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,parser->getAmbientLight());
    
    //DRAWING PROPERTIES
    if((strcmp (parser->getShading(),"flat")==0)){
        glShadeModel(GL_FLAT);
    }else {
        glShadeModel(GL_SMOOTH);
    }
    
    if((strcmp (parser->getDrawingMode(),"fill")==0)){
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }else if(strcmp(parser->getDrawingMode(),"point")==0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }else if(strcmp (parser->getDrawingMode(),"line")==0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

	//background color
	float* backColor = parser->getBackgroundColor();
	glClearColor(backColor[0],backColor[1],backColor[2],backColor[3]);
 
    
    setUpdatePeriod(30);
}

void XMLScene::update(unsigned long t) {
    shader->bind();
    shader->update(t/400.0);
    shader->unbind();
}

void XMLScene::display() {
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Apply transformations corresponding to the camera position relative to the origin
    CGFscene::activeCamera->applyView();
    
    // Draw axis
    axis.draw();
   
    
    glutSwapBuffers();
}

XMLScene::~XMLScene() {
    delete(shader);
}




