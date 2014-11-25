
#include "Section.h"
using namespace std;

Section::Section(int x,int y) {
	this->x=x;
	this->y=y;
}

Section::~Section() {
	// TODO Auto-generated destructor stub
}

void Section::draw(){
	glBegin(GL_QUADS);
		glVertex3d(0,0,0);
		glVertex3d(1,0,0);
		glVertex3d(1,1,0);
		glVertex3d(0,1,0);
	glEnd();
}
