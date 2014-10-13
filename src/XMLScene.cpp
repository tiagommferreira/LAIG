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
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");
	parser = new XMLParser();

	cout <<  endl << endl << endl <<"_____ OPEN GL ______" << endl << endl;

	cout << "__globals__" << endl << endl;
	/* GLOBALS */
	cout << "culling properties" << endl;
	// CULLING PROPERTIES
	if((strcmp (parser->getGlobals()->getOrder(),"cw")==0)){
		glFrontFace(GL_CW);
	}else {
		glFrontFace(GL_CCW);
	}

	// also has the possibility to be none
	if((strcmp(parser->getGlobals()->getFace(),"front")==0)){
		glCullFace(GL_FRONT);
	}else if((strcmp (parser->getGlobals()->getFace(),"back")==0)){
		glCullFace(GL_BACK);
	}

	cout << "lighting properties" << endl;
	//LIGHTING PROPERTIES
	if((strcmp (parser->getGlobals()->getEnabled(),"true")==0)){
		glEnable(GL_LIGHTING);
	}
	if((strcmp (parser->getGlobals()->getLocal(),"true")==0)){
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	}
	if((strcmp (parser->getGlobals()->getDoublesided(),"true")==0)){
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,parser->getGlobals()->getAmbientLight());

	cout << "drawing properties" << endl;
	//DRAWING PROPERTIES
	if((strcmp (parser->getGlobals()->getShading(),"flat")==0)){
		glShadeModel(GL_FLAT);
	}else {
		glShadeModel(GL_SMOOTH);
	}

	if((strcmp (parser->getGlobals()->getDrawingMode(),"fill")==0)){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else if(strcmp(parser->getGlobals()->getDrawingMode(),"point")==0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}else if(strcmp (parser->getGlobals()->getDrawingMode(),"line")==0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	//background color
	float* backColor = parser->getGlobals()->getBackgroundColor();
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
	//CGFscene::activeCamera->applyView();
	vector<Camera*> cameras = parser->getCameras();
	Camera *initialCamera = new Camera();

	for(int i=0;i<cameras.size();i++){
		if(strcmp(cameras[i]->getId(),cameras[i]->getInitial())==0){
			initialCamera = cameras[i];
			break;
		}
	}

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	if(initialCamera->getType() == 1){
		if(initialCamera->getOrthoDirection() == 'x') {
			glRotated(90,0,1,0);
			glScaled(1, 1, -1);
		}
		else if(initialCamera->getOrthoDirection() == 'y') {
			glRotated(90,1,0,0);
			glScaled(1, -1, 1);
		}

		glOrtho(initialCamera->getOrthoLeft(), initialCamera->getOrthoRight(), initialCamera->getOrthoBottom(), initialCamera->getOrthoTop(), initialCamera->getOrthoNear(), initialCamera->getOrthoFar());

	} else {
		gluPerspective(initialCamera->getPerspecAngle(), 1, initialCamera->getPerspecNear(), initialCamera->getPerspecFar());
		gluLookAt(initialCamera->getPerspecPos()[0], initialCamera->getPerspecPos()[1], initialCamera->getPerspecPos()[2],
				initialCamera->getPerspecTarget()[0], initialCamera->getPerspecTarget()[1], initialCamera->getPerspecTarget()[2],
				0,1,0);
	}

	glMatrixMode(GL_MODELVIEW);
	// Draw axis
	axis.draw();

	/** GRAPH **/
	float m[4][4];
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,&m[0][0]);

	map<char*,Node*> temp = parser->getGraph();
	map<char*,Node*>::iterator it=temp.begin();
	for(unsigned int i=0;i<temp.size();i++,it++){
		if(strcmp(parser->getRootid(),it->second->getId())==0){
			it->second->draw(m);
			break;
		}
	}

	glutSwapBuffers();
}

XMLScene::~XMLScene() {
	delete(shader);
}
