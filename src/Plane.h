#ifndef __CGFExample__Plane__
#define __CGFExample__Plane__

#include "CGFtexture.h"
#include <GL/glut.h>

class Plane{
public:
		void draw();
		Plane();
		~Plane();
	private:
		CGFtexture *myTexture;
};
#endif
