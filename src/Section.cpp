
#include "Section.h"
Section::Section(){
}

Section::~Section() {
	// TODO Auto-generated destructor stub
}

void Section::draw(){
	glBegin(GL_QUADS);
        glTexCoord2d(0,0);
		glVertex3d(0,0,0);
        glTexCoord2d(1,0);
		glVertex3d(1,0,0);
        glTexCoord2d(1,1);
		glVertex3d(1,1,0);
        glTexCoord2d(0,1);
		glVertex3d(0,1,0);
	glEnd();
}
