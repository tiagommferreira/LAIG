#include "Plane.h"
#include <GL/glut.h>

GLfloat ctrlpoints[4][3] = {	{  -0.5, 0.0, 0.5},
								{  -0.5, 0.0, -0.5},
								{ 0.5, 0.0, 0.5},
								{ 0.5, 0.0, -0.5} };

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



Plane::Plane(CGFtexture *texture,int uPatches, int vPatches,int degree){
	this->texture=texture;
	this->uPatches=uPatches;
	this->vPatches=vPatches;
	this->degree=degree;
}

Plane::~Plane() {
	delete(texture);
}

void Plane::draw(){

	//TODO GL_AUTO_NORMAL ? ver se é preciso

	//TODO por os pontos de controlo de forma dinamica
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, degree,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, degree,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, degree,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, degree,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	//TODO por dinamico aqui e no EvalMesh
	glMapGrid2f(uPatches, 0.0,1.0, vPatches, 0.0,1.0);

	//TODO verificar se é preciso voltar a definir aqui o shadeModel
	//glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	//TODO adicionar texture
	//this->texture->apply();


	//TODO ver esta parte do fill ou line consuante o que tiver definido anteriormente
	glEvalMesh2(GL_FILL, 0,uPatches, 0,vPatches);// GL_POINT, GL_LINE, GL_FILL

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}
