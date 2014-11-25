
#ifndef SRC_SECTION_H_
#define SRC_SECTION_H_

using namespace std;
#include "CGFobject.h"

class Section :public CGFobject{
private:
	int x;
	int y;
public:
	Section(int,int);
	void draw();
	virtual ~Section();
};


#endif /* SRC_SECTION_H_ */
