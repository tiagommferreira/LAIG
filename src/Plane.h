#ifndef __CGFExample__Plane__
#define __CGFExample__Plane__

#include "CGFtexture.h"
#include <GL/glut.h>

class Plane{
public:
		void draw();
		Plane(CGFtexture*,int,int,int);
		~Plane();
	private:
		CGFtexture *texture;
		int vPatches,uPatches;
		int degree;
};
#endif
