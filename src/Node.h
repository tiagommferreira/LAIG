
#ifndef __CGFExample__Node__
#define __CGFExample__Node__

#include <stdio.h>
#include <vector>
#include "Primitive.h"
#include "Transform.h"
#include "Animation.h"
#include "Evaluator.h"
#include <cmath>

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

	GLuint index;
	//second project
	float animationMatrix[4][4];
	bool displayList;
	bool animated;
	int currentAnimation;
	//general animation
	vector<Animation*> animations;

public:
	Node(){processed = false;displayList=false;currentAnimation=0;}

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
		float a,b,c;
		a = sqrt((xyz3[0]-xyz2[0])*(xyz3[0]-xyz2[0])) + (xyz3[1]-xyz2[1])* (xyz3[1]-xyz2[1]) + (xyz3[2]-xyz2[2])*(xyz3[2]-xyz2[2]);
		b = sqrt((xyz1[0]-xyz3[0])*(xyz1[0]-xyz3[0])) + (xyz1[1]-xyz3[1])* (xyz1[1]-xyz3[1]) + (xyz1[2]-xyz3[2])*(xyz1[2]-xyz3[2]);
		c = sqrt((xyz2[0]-xyz1[0])*(xyz2[0]-xyz1[0])) + (xyz2[1]-xyz1[1])* (xyz2[1]-xyz1[1]) + (xyz2[2]-xyz1[2])*(xyz2[2]-xyz1[2]);

		float cosA,cosB,cosY;
		cosA = (-(a*a) + b*b + c*c ) / (2 * b * c);
		cosB = ( (a*a) + -(b*b) + c*c) / (2*a*c);
		cosY = ( a*a + b*b -(c*c)) / (2*a*b);

		float angA, angB, angY;
		angA = acos(cosA);
		angB = acos(cosB);
		angY = acos(cosY);


		glNormal3f(0,0,1);
		glBegin(GL_POLYGON);
		glTexCoord2d(0,0);
		glVertex3f(xyz1[0],xyz1[1], xyz1[2]);
		glTexCoord2d(c,0);
		glVertex3f(xyz2[0],xyz2[1], xyz2[2]);
		glTexCoord2d(c - a*cosB, a*sin(angB));
		glVertex3f(xyz3[0],xyz3[1], xyz3[2]);
		glEnd();
	}

	void drawCylinder(float base,float top, float height, int slices, int stacks){
		GLUquadric *quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic, true);
		gluCylinder(quadratic, base, top, height, slices, stacks);
		double pos = 0.0;
		double incAngle = 360.0/12.0;
		double delta = 2*(3.1415)/slices;
		double angle = 0;
		double posTextX = 0.0;
		double posTextY = 0.0;

		glPushMatrix();
		glRotated(180,0,1,0);
		glScaled(base,base,0);
		for(int i=0; i < slices; i++) {
			glBegin(GL_TRIANGLES);
			glTexCoord2d((cos(angle + delta) * 0.5)+0.5 ,(sin(angle + delta) * 0.5)+0.5);
			glVertex3d(cos(angle+delta),sin(angle+delta),1);
			glTexCoord2d(0.5, 0.5);
			glVertex3d(0,0,1);
			glTexCoord2d((cos(angle)* 0.5)+0.5,(sin(angle)*0.5)+0.5);
			glVertex3d(cos(angle),sin(angle),1);
			glEnd();
			angle += delta;
			posTextX += incAngle;
		}
		glPopMatrix();

		glPushMatrix();
		glTranslated(0,0,height);
		glScaled(top,top,0);
		for(int i=0; i < slices; i++) {
			glBegin(GL_TRIANGLES);
			glTexCoord2d((cos(angle + delta) * 0.5)+0.5 ,(sin(angle + delta) * 0.5)+0.5);
			glVertex3d(cos(angle+delta),sin(angle+delta),1);
			glTexCoord2d(0.5, 0.5);
			glVertex3d(0,0,1);
			glTexCoord2d((cos(angle)* 0.5)+0.5,(sin(angle)*0.5)+0.5);
			glVertex3d(cos(angle),sin(angle),1);
			glEnd();
			angle += delta;
			posTextX += incAngle;
		}
		glPopMatrix();
	}

	void drawSphere(float radious, int slices, int stacks){
		GLUquadric *quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic, true);
		gluSphere(quadratic,radious, slices, stacks);
	}

	void drawTorus(float inner,float outter, int slices, int loops){
		//glutSolidTorus(inner, outter, slices, loops);
		double pi = acos(-1.0);
		float vNormal[3];
		double majorStep = 2.0f*pi / slices;
		double minorStep = 2.0f*pi / loops;
		int i, j;

		for (i=0; i<slices; ++i)
		{
			double a0 = i * majorStep;
			double a1 = a0 + majorStep;
			GLfloat x0 = (GLfloat) cos(a0);
			GLfloat y0 = (GLfloat) sin(a0);
			GLfloat x1 = (GLfloat) cos(a1);
			GLfloat y1 = (GLfloat) sin(a1);

			glBegin(GL_TRIANGLE_STRIP);
			for (j=0; j<=loops; ++j)
			{
				double b = j * minorStep;
				GLfloat c = (GLfloat) cos(b);
				GLfloat r = inner * c + outter;
				GLfloat z = inner * (GLfloat) sin(b);

				// First point
				glTexCoord2f((float)(i)/(float)(loops), (float)(j)/(float)(slices));
				vNormal[0] = x0*c;
				vNormal[1] = y0*c;
				vNormal[2] = z/inner;
				//glNormalizeVector(vNormal);
				glNormal3fv(vNormal);
				glVertex3f(x0*r, y0*r, z);

				glTexCoord2f((float)(i+1)/(float)(loops), (float)(j)/(float)(slices));
				vNormal[0] = x1*c;
				vNormal[1] = y1*c;
				vNormal[2] = z/inner;
				glNormal3f(vNormal[0],vNormal[1],vNormal[2]);
				glVertex3f(x1*r, y1*r, z);
			}
			glEnd();
		}
	}

	void calculateAnimations(){
		animations[currentAnimation]->setOver(false);
		// se for animado ignora-se as transformacoes
		if(this->animations[currentAnimation]->getType()==0){
			CircularAnimation *circ = (CircularAnimation*) this->animations[currentAnimation];
			circ->setCurrentAngle(0); // sets the initial angle to 0
			circ->setDeltaAngle(circ->getRotationAngle() / (33.3 * circ->getTime()));  // TODO tirar o hardcoded 33.3(update period time)
			this->animations[currentAnimation] = circ;

		}else {
			LinearAnimation *linear = (LinearAnimation*) this->animations[currentAnimation];
			linear->setCurrentX(linear->getControlPoints()[0][0]);
			linear->setCurrentY(linear->getControlPoints()[0][1]);
			linear->setCurrentZ(linear->getControlPoints()[0][2]);
			float fullDistance=0;
			for(unsigned int i=0;i<linear->getControlPoints().size()-1;i++){
				float currentDistance=sqrt(pow((linear->getControlPoints()[i+1][0]-linear->getControlPoints()[i][0]),2)+
						pow((linear->getControlPoints()[i+1][1]-linear->getControlPoints()[i][1]),2) +
						pow((linear->getControlPoints()[i+1][2]-linear->getControlPoints()[i][2]),2));
				fullDistance += currentDistance;
				linear->addDistance(currentDistance);

			}
			linear->addDistance(fullDistance);



			for(unsigned int i=0;i<linear->getControlPoints().size()-1;i++){
				float deltaX,deltaY,deltaZ;
				deltaX = (linear->getControlPoints()[i+1][0]-linear->getControlPoints()[i][0])
																						/ (linear->getDistances()[i]*linear->getTime()/
																								linear->getDistances()[linear->getControlPoints().size()-1] * 33.333);
				deltaY = (linear->getControlPoints()[i+1][1]-linear->getControlPoints()[i][1])
																						/ (linear->getDistances()[i]*linear->getTime()/
																								linear->getDistances()[linear->getControlPoints().size()-1] * 33.333);
				deltaZ = (linear->getControlPoints()[i+1][2]-linear->getControlPoints()[i][2])
																						/ (linear->getDistances()[i]*linear->getTime()/
																								linear->getDistances()[linear->getControlPoints().size()-1] * 33.333);

				linear->addDeltaX(deltaX);
				linear->addDeltaY(deltaY);
				linear->addDeltaZ(deltaZ);
			}

			linear->setCurrentAnimState(0);
			this->animations[currentAnimation] = linear;
		}
	}

	void setAnimationMatrix(){
		glPushMatrix();
		glLoadIdentity();
		animations[currentAnimation]->setOver(false);

		// se for animado ignora-se as transformacoes
		if(this->animations[currentAnimation]->getType()==0){
			CircularAnimation *circ = (CircularAnimation*) this->animations[currentAnimation];
			glTranslated(circ->getCenter()[0],circ->getCenter()[1],circ->getCenter()[2]); // poem na posicao inicial
			glRotated(circ->getInitAngle(),0,0,1); // roda o angulo inicial

		}else {
			LinearAnimation *linear = (LinearAnimation*) this->animations[currentAnimation];
		}
		glGetFloatv(GL_MODELVIEW_MATRIX, &animationMatrix[0][0]);
		glPopMatrix();
	}

	void createDisplayList(){
		this->index = glGenLists(primitives.size());

		for(unsigned int i=0;i<primitives.size();i++) {
			glNewList(index+i, GL_COMPILE);
			drawPrimitives();
			glEndList();
		}
	}


	void setMatrix(){
		glPushMatrix();
		glLoadIdentity();

		// se nao faz as transformacoes normalmente
		for(unsigned int i = 0; i < transforms.size(); i++) {
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
			} else if(strcmp(primitives[i]->getValue(),"plane")==0) {
				Plane* plane = (Plane*) primitives[i];

				GLfloat ctrlpoints[4][3] = {	{  -0.5, 0.0, 0.5},
												{  -0.5, 0.0, -0.5},
												{ 0.5, 0.0, 0.5},
												{ 0.5, 0.0, -0.5} };

				Evaluator* eval = new Evaluator(NULL, plane->getParts(),plane->getParts(),2,"fill", &ctrlpoints[0][0]);
				eval->drawPlane();
			} else if(strcmp(primitives[i]->getValue(),"patch")==0) {
				Patch* patch = (Patch*) primitives[i];
				vector<vector<GLfloat> > points = patch->getPoints();
				GLfloat ctrlpoints[points.size()][3];
				for(int i = 0; i<points.size();i++){
					for(int j = 0; j<3;j++){
						ctrlpoints[i][j] = points[i][j];
					}
				}
				Evaluator* eval = new Evaluator(NULL, patch->getPartsU(),patch->getPartsV(),
						patch->getOrder(),patch->getCompute(),&ctrlpoints[0][0]);
				eval->drawPatch();
			}else if(strcmp(primitives[i]->getValue(),"vehicle")==0) {
				Vehicle* v = (Vehicle*) primitives[i];
				v->draw();
			}
		}
	}

	void update(){
		if(!animations[currentAnimation]->isOver()){
			if(animations[currentAnimation]->getType()==0){
				//circular animation
				CircularAnimation *circ = (CircularAnimation*) this->animations[currentAnimation];
				if(circ->getRotationAngle() > circ->getCurrentAngle()){
					circ->setCurrentAngle(circ->getCurrentAngle() + circ->getDeltaAngle());
				} else{
					circ->setOver(true);
				}
				this->animations[currentAnimation] = circ;
			}else {

				LinearAnimation *linear = (LinearAnimation*) this->animations[currentAnimation];
				//linear animation
				linear->setCurrentX(linear->getCurrentX()+linear->getDeltaX()[linear->getCurrentAnimState()]);
				linear->setCurrentY(linear->getCurrentY()+linear->getDeltaY()[linear->getCurrentAnimState()]);
				linear->setCurrentZ(linear->getCurrentZ()+linear->getDeltaZ()[linear->getCurrentAnimState()]);

				float newDistance =sqrt(pow((linear->getCurrentX()-linear->getControlPoints()[linear->getCurrentAnimState()+1][0]),2)+
						pow((linear->getCurrentY()-linear->getControlPoints()[linear->getCurrentAnimState()+1][1]),2) +
						pow((linear->getCurrentZ()-linear->getControlPoints()[linear->getCurrentAnimState()+1][2]),2));

				if(newDistance - linear->getLastDistance() > 0){

					linear->setCurrentAnimState(linear->getCurrentAnimState()+1);

					if(linear->getCurrentAnimState() == linear->getControlPoints().size()-1 ){
						linear->setOver(true);
					} else {
						newDistance =sqrt(pow((linear->getCurrentX()-linear->getControlPoints()[linear->getCurrentAnimState()+1][0]),2)+
								pow((linear->getCurrentY()-linear->getControlPoints()[linear->getCurrentAnimState()+1][1]),2) +
								pow((linear->getCurrentZ()-linear->getControlPoints()[linear->getCurrentAnimState()+1][2]),2));
						linear->setLastDistance(newDistance);
					}
				}


				linear->setLastDistance(newDistance);
				this->animations[currentAnimation] = linear;
			}

		} else {
			if(currentAnimation < animations.size()-1){
				currentAnimation++;
				calculateAnimations();
				setAnimationMatrix();
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

		if(this->isAnimated()){//se for animado

			if(this->animations[currentAnimation]->getType()==0){
				// circular
				CircularAnimation *circ = (CircularAnimation*) this->animations[currentAnimation];
				glMultMatrixf(&animationMatrix[0][0]);
				glRotated(circ->getCurrentAngle(),0,1,0);
				glTranslated(circ->getRadious(),0,0); // incrementa o raio da animacao
			} else {
				// linear
				LinearAnimation *linear = (LinearAnimation*) this->animations[currentAnimation];
				glTranslated(linear->getCurrentX(),linear->getCurrentY(),linear->getCurrentZ());
				glMultMatrixf(&animationMatrix[0][0]);
			}
		} else {// se nao for animado
			if(transforms.size()!=0){
				glMultMatrixf(&transformMatrix[0][0]);
			}
		}

		if(isDisplayList()){
			glCallList(index);
		} else {
			//senao desenha as primitivas normalmente
			if(primitives.size()!=0) {
				drawPrimitives();
			}
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

	bool isAnimated() const {
		return animated;
	}

	void setAnimated(bool animated) {
		this->animated = animated;
	}

	void setAnimation( Animation* animation) {
		this->animations.push_back(animation);
	}

	bool isDisplayList() const {
		return displayList;
	}

	void setDisplayList(bool displayList) {
		this->displayList = displayList;
	}
};
#endif /* defined(__CGFExample__Node__) */
