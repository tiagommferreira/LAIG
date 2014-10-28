#ifndef __CGFExample__Evaluator__
#define __CGFExample__Evaluator__

#include "CGFtexture.h"
#include <GL/glut.h>

class Evaluator{
public:
		void draw();
		Evaluator(CGFtexture*,int,int,int,char*);
		~Evaluator();
	private:
		CGFtexture *texture;
		int vPatches,uPatches;
		int degree;
		char* compute;
};
#endif
