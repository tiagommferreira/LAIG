
#ifndef SRC_SECTION_H_
#define SRC_SECTION_H_

using namespace std;
#include "CGFobject.h"

class Section :public CGFobject{
private:

public:
	Section();
	void draw();    
	virtual ~Section();
};

#endif /* SRC_SECTION_H_ */
