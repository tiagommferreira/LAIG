#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include <vector>
#include "Section.h"
#include "CGFappearance.h"
#include "Primitive.h"
#include <iostream>

class Board: public Primitive {
private:
	std::vector<std::vector< Section *> > board;
public:
	Board();
	void draw();
    CGFappearance * app1;
    CGFappearance * app2;
	virtual ~Board();
};

#endif
