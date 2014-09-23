#include "XMLScene.h"
#include "CGFappearance.h"
#include "ExampleObject.h"
#include "CGFapplication.h"
#include "CGFaxis.h"
#include "XMLParser.h"
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
    char *p = "/Users/ricardo/Documents/Laig/CGFlib/CGFexample/data/demograph.xml";
    parser = XMLParser(p);
    
    glEnable(GL_LIGHTING);
    
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);
    
    shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");
    
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
    
    /** GLOBALS **/
    
    // lighting
    
    
    // drawing
    
    
    // culling
    if(parser.getFace()=="front"){
        glCullFace(GL_FRONT);
    } else if(parser.getFace()=="back"){
        glCullFace(GL_BACK);
    }
    
    glutSwapBuffers();
}

XMLScene::~XMLScene() {
    delete(shader);
}




