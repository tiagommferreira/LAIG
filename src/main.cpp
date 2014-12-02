
#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "XMLScene.h"
#include "XMLParser.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();
    CGFscene * scene;
    try {
		app.init(&argc, argv);
		app.setScene(scene = new XMLScene());
        app.setInterface(new PickInterface());
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}