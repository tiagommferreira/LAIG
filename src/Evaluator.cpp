#include "Evaluator.h"
#include <string.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLfloat nrmlcompon[4][3] = {	{  0.0, 1.0, 0.0},
		{  0.0, 1.0, 0.0},
		{  0.0, 1.0, 0.0},
		{  0.0, 1.0, 0.0} };

GLfloat colorpoints[4][4] = {	{ 0.5, 0.5, 0.5, 0},
		{ 0.5, 0.5, 0.5, 0},
		{ 0.5, 0.5, 0.5, 0},
		{ 0.5, 0.5, 0.5, 0} };

GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
		{ 0.0, 1.0},
		{ 1.0, 0.0},
		{ 1.0, 1.0} };



Evaluator::Evaluator(CGFtexture *texture,int uPatches, int vPatches,int degree, char* compute, GLfloat* ctrlpoints){
	this->texture=texture;
	this->uPatches=uPatches;
	this->vPatches=vPatches;
	this->degree=degree+1;
	this->compute=compute;
	this->ctrlpoints = ctrlpoints;
}

Evaluator::~Evaluator() {
	delete(texture);
}

void Evaluator::drawPatch(){
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, degree,  0.0, 1.0, 12, 4,  ctrlpoints);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, degree,  0.0, 1.0, 6, 3,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, degree,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(uPatches, 0.0,1.0, vPatches, 0.0,1.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);


	if(strcmp(this->compute, "point") == 0) {
		glEvalMesh2(GL_POINT, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}
	else if(strcmp(this->compute, "line") == 0) {
		glEvalMesh2(GL_LINE, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}
	else if(strcmp(this->compute, "fill") == 0) {
		glEvalMesh2(GL_FILL, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}

void Evaluator::drawPlane(){

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, ctrlpoints);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 2 * 2, 2, &textpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);


	glMapGrid2f(this->uPatches, 0.0, 1.0, this->uPatches, 0.0, 1.0);
	if(strcmp(this->compute, "point") == 0) {
		glEvalMesh2(GL_POINT, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}
	else if(strcmp(this->compute, "line") == 0) {
		glEvalMesh2(GL_LINE, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}
	else if(strcmp(this->compute, "fill") == 0) {
		glEvalMesh2(GL_FILL, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL
	}


	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
}
