
#ifndef __CGFExample__Node__
#define __CGFExample__Node__

#include <stdio.h>
#include <vector>
#include "Primitive.h"
#include "Transform.h"

using namespace std;

class Node {
private:
	vector<Node*> graph;
	vector<Primitive *> primitives;
	vector<Transform *> transforms;
	char * appearenceRef;
	vector<Node *> descendents;
	float transformMatrix[4][4];
	char * id;
	bool processed;
	CGFappearance * appearance = new CGFappearance();
	CGFappearance * parentAppearance = new CGFappearance();

public:
	Node(){processed = false;}

	void setAppearance(CGFappearance * app){
		this->appearance = app;
	}

	CGFappearance * getAppearance() {
		return this->appearance;
	}

	void setAllPrimitives(vector<Primitive *> prim) {
		this->primitives = prim;
	}

	void setAllTransforms(vector<Transform * >trans){
		this->transforms = trans;
	}

	void addPrimitive(Primitive *currentPrimitive){
		this->primitives.push_back(currentPrimitive);
	}

	void addTransform(Transform * currentTransform){
		this->transforms.push_back(currentTransform);
	}

	void setAppearence(char * appearenceName){
		this->appearenceRef = appearenceName;
	}

	void setDescendents(Node * descendent){
		this->descendents.push_back(descendent);
	}

	void setAppearenceRef(char* appearenceRef) {
		this->appearenceRef = appearenceRef;
	}

	char* getAppearenceRef() const {
		return appearenceRef;
	}

	vector<Node*>& getDescendents() {
		return descendents;
	}

	const vector<Primitive*>& getPrimitives() const {
		return primitives;
	}

	const vector<Transform*>& getTransforms() const {
		return transforms;
	}

	char* getId() const {
		return id;
	}

	void setId(char* id) {
		this->id = id;
	}

	void drawRectangle(float xy1[2],float xy2[2]){
		glNormal3f(0,0,1);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3d(xy1[0],xy1[1],0);
		glTexCoord2d(1,0);
		glVertex3d(xy2[0],xy1[1],0);
		glTexCoord2d(1,1);
		glVertex3d(xy2[0],xy2[1],0);
		glTexCoord2d(0,1);
		glVertex3d(xy1[0],xy2[1],0);
		glEnd();
	}

	void drawTriangle(float xyz1[3],float xyz2[3], float xyz3[3]){
		glNormal3f(0,0,1);
		glBegin(GL_POLYGON);
		glVertex3f(xyz1[0],xyz1[1], xyz1[2]);
		glVertex3f(xyz2[0],xyz2[1], xyz2[2]);
		glVertex3f(xyz3[0],xyz3[1], xyz3[2]);
		glEnd();
	}

	void drawCylinder(float base,float top, float height, int slices, int stacks){
		gluCylinder(gluNewQuadric(), base, top, height, slices, stacks);
	}

	void drawSphere(float radious, int slices, int stacks){
		gluSphere(gluNewQuadric(),radious, slices, stacks);
	}

	void drawTorus(float inner,float outter, int slices, int loops){
		glutSolidTorus(inner, outter, slices, loops);
	}

	void setMatrix(){
		glPushMatrix();
		glLoadIdentity();

		for(int i = 0; i < transforms.size(); i++) {

			cout << "transform type: " << transforms[i]->getType() << endl;

			if(strcmp(transforms[i]->getType(), "translate") == 0) {
				glTranslated(transforms[i]->getTo()[0],transforms[i]->getTo()[1],transforms[i]->getTo()[2]);
			}
			else if(strcmp(transforms[i]->getType(), "rotate") == 0) {
				cout << "ROTATE " << transforms[i]->getAxis() << " " << transforms[i]->getAngle() << endl;
				if(transforms[i]->getAxis() == 'x') {
					glRotated(transforms[i]->getAngle(),1,0,0);
				}
				else if(transforms[i]->getAxis() == 'y') {
					glRotated(transforms[i]->getAngle(),0,1,0);
				}
				else if(transforms[i]->getAxis() == 'z') {
					glRotated(transforms[i]->getAngle(),0,0,1);
				}
			}
			else if(strcmp(transforms[i]->getType(), "scale") == 0) {
				glScaled(transforms[i]->getFactor()[0],transforms[i]->getFactor()[1],transforms[i]->getFactor()[2]);
			}
		}

		glGetFloatv(GL_MODELVIEW_MATRIX, &transformMatrix[0][0]);
		glPopMatrix();
	}

	float* getTransformMatrix() {
		return &transformMatrix[0][0];
	}

	bool isProcessed() const {
		return processed;
	}

	void setProcessed(bool processed) {
		this->processed = processed;
	}

	void setAllDescendents(vector<Node*> nodes) {
		this->descendents = nodes;
	}

	void drawPrimitives() {
		for(unsigned int i = 0; i < primitives.size(); i++) {
			if(strcmp(primitives[i]->getValue(), "rectangle") == 0) {
				drawRectangle(
						primitives[i]->getXY1(),
						primitives[i]->getXY2());
			}
			else if(strcmp(primitives[i]->getValue(), "triangle") == 0) {
				drawTriangle(
						primitives[i]->getXYZ1(),
						primitives[i]->getXYZ2(),
						primitives[i]->getXYZ3());
			}
			else if(strcmp(primitives[i]->getValue(), "cylinder") == 0) {
				drawCylinder(
						primitives[i]->getBase(),
						primitives[i]->getTop(),
						primitives[i]->getHeight(),
						primitives[i]->getSlices(),
						primitives[i]->getStacks());
			}
			else if(strcmp(primitives[i]->getValue(), "sphere") == 0) {
				drawSphere(
						primitives[i]->getRadius(),
						primitives[i]->getSlices(),
						primitives[i]->getStacks());
			}
			else if(strcmp(primitives[i]->getValue(), "torus") == 0) {
				drawTorus(
						primitives[i]->getInner(),
						primitives[i]->getOutter(),
						primitives[i]->getSlices(),
						primitives[i]->getLoops());
			}
		}
	}

	void draw(){

		if(strcmp(appearenceRef,"inherit")==0 || strcmp(appearenceRef,"")==0){
			parentAppearance->apply();
		} else {
			appearance->apply();
		}

		glPushMatrix();

		if(transforms.size()!=0){
			glMultMatrixf(&transformMatrix[0][0]);
		}
		else {
		}

		if(primitives.size()!=0) {
			drawPrimitives();
		}else{
		}

		for(unsigned int i=0;i<descendents.size();i++) {
			descendents[i]->draw();
		}
		glPopMatrix();
	}

	CGFappearance* getParentAppearance() {
		return parentAppearance;
	}

	void setParentAppearance(CGFappearance* parentAppearance) {
		this->parentAppearance = parentAppearance;
	}
};
#endif /* defined(__CGFExample__Node__) */
