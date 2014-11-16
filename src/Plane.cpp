#include "Plane.h"
#include <GL/glut.h>

Plane::Plane(){

}

Plane::~Plane() {
	delete(myTexture);
}
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

void Plane::draw(){

	//TODO verificar os valores predefinidos se estao correctos e ver como extender para curvas de maior grau
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	//TODO por dinamico aqui e no EvalMesh
	glMapGrid2f(5, 0.0,1.0, 5, 0.0,1.0);


	// SEGUE-SE EXEMPLO DE UTILIZACAO DE "EVALUATORS"
	//glShadeModel(GL_FLAT);					// GL_FLAT, GL_SMOOTH
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	//TODO ver esta parte do fill ou line consuante o que tiver definido anteriormente
	glEvalMesh2(GL_FILL, 0,5, 0,5);		// GL_POINT, GL_LINE, GL_FILL

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}
