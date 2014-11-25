#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include <vector>
#include "Section.h"
#include <iostream>

class Board {
private:
	std::vector<std::vector< Section *> > board;
public:
	Board();
	void draw();

	virtual ~Board();
};

#endif
