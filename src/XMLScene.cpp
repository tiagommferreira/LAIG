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
	/* GLOBALS */

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
	map<char*,Node*>::iterator atual=parser->getGraph().begin();

	for(int i = 0;i < parser->getGraph().size();i++,atual++) {
		vector<Primitive*> primitives = atual->second->getPrimitives();

		if(atual->second->getTransforms().size() != 0)
				glLoadMatrixf(atual->second->getTransformMatrix());

		cout << "PRIMITIVES SIZE: " << primitives.size() << endl;
		for(int j = 0; j < primitives.size(); j++) {
			if(strcmp(primitives[j]->getValue(), "rectangle") == 0) {
				drawRectangle(parser->getGlobals()->getOrder(),
						primitives[j]->getXY1(),
						primitives[j]->getXY2());
			}
			else if(strcmp(primitives[j]->getValue(), "triangle") == 0) {
				drawTriangle(parser->getGlobals()->getOrder(),primitives[j]->getXYZ1(),
						primitives[j]->getXYZ2(),
						primitives[j]->getXYZ3());
			}
			else if(strcmp(primitives[j]->getValue(), "cylinder") == 0) {
				drawCylinder(parser->getGlobals()->getOrder(),
						primitives[j]->getBase(),
						primitives[j]->getTop(),
						primitives[j]->getHeight(),
						primitives[j]->getSlices(),
						primitives[j]->getStacks());
			}
			else if(strcmp(primitives[j]->getValue(), "sphere") == 0) {
				drawSphere(parser->getGlobals()->getOrder(),
						primitives[j]->getRadius(),
						primitives[j]->getSlices(),
						primitives[j]->getStacks());
			}
			else if(strcmp(primitives[j]->getValue(), "torus") == 0) {
				drawTorus(parser->getGlobals()->getOrder(),
						primitives[j]->getInner(),
						primitives[j]->getOutter(),
						primitives[j]->getSlices(),
						primitives[j]->getLoops());
			}
		}
	}

	glutSwapBuffers();
}

XMLScene::~XMLScene() {
	delete(shader);
}

void XMLScene::drawRectangle(string type,float xy1[2],float xy2[2]){
	cout << "DRAWING RECTANGLE" << endl;
	if(type=="cw"){
		glBegin(GL_POLYGON);
		glVertex2f(xy1[0],xy1[1]);
		glVertex2f(xy1[0],xy2[1]);
		glVertex2f(xy2[0],xy2[1]);
		glVertex2f(xy2[0],xy1[1]);
		glEnd();
	} else{
		glBegin(GL_POLYGON);
		glVertex2f(xy1[0],xy1[1]);
		glVertex2f(xy2[0],xy1[1]);
		glVertex2f(xy2[0],xy2[1]);
		glVertex2f(xy1[0],xy2[1]);
		glEnd();
	}
}

void XMLScene::drawTriangle(string type,float xyz1[3],float xyz2[3], float xyz3[3]){
	cout << "DRAWING TRIANGLE" << endl;
	if(type=="cw"){
		glBegin(GL_POLYGON);
		glVertex3f(xyz1[0],xyz1[1], xyz1[2]);
		glVertex3f(xyz2[0],xyz2[1], xyz2[2]);
		glVertex3f(xyz3[0],xyz3[1], xyz3[2]);
		glEnd();
	} else{
		glBegin(GL_POLYGON);
		glVertex3f(xyz3[0],xyz3[1], xyz3[2]);
		glVertex3f(xyz2[0],xyz2[1], xyz2[2]);
		glVertex3f(xyz1[0],xyz1[1], xyz1[2]);
		glEnd();
	}
}

void XMLScene::drawCylinder(string type,float base,float top, float height, int slices, int stacks){
	cout << "DRAWING CYLINDER" << endl;
	//gluCylinder(gluNewQuadric(), base, top, height, slices, stacks);

}

void XMLScene::drawSphere(string type,float radious, int slices, int stacks){
	cout << "DRAWING SPHERE" << endl;
	glutSolidSphere(radious, slices, stacks);

}


void XMLScene::drawTorus(string type,float inner,float outter, int slices, int loops){
	cout << "DRAWING TORUS" << endl;
	//glutSolidTorus(inner, outter, slices, loops);
}




