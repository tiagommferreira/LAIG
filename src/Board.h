#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include <vector>
#include "Section.h"
#include "CGFappearance.h"
#include "Primitive.h"
#include "Stack.h"
#include <iostream>
using namespace std;

class Board: public Primitive {
private:
    Section* section;
    vector<vector< Stack *> > currentState;
public:
	Board();
	void draw();
    CGFappearance * app1;
    CGFappearance * app2;
	virtual ~Board();
};

#endif
