#ifndef __CGFExample__Evaluator__
#define __CGFExample__Evaluator__

#include "CGFtexture.h"
#include <GLUT/glut.h>

class Evaluator{
public:
		void drawPatch();
		void drawPlane();
		Evaluator(CGFtexture*,int,int,int,char*,GLfloat*);
		~Evaluator();
	private:
		CGFtexture *texture;
		int vPatches,uPatches;
		int degree;
		char* compute;
		GLfloat* ctrlpoints;
};
#endif
