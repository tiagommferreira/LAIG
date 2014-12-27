
#ifndef __CGFExample__Stack__
#define __CGFExample__Stack__

#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

class Stack {
private:
	int numberOfPieces;
	int player;
	CGFappearance * text;
	bool animated, zAscending;
	vector<int> animStartPoint;
	float xAnim, yAnim, zAnim;
	string animType;
public:
	Stack(int numberOfPieces, int player){
		this->numberOfPieces=numberOfPieces;
		this->player=player;
		CGFtexture * temp;
		this->animated = false;
		this->xAnim = 0;
		this->yAnim = 0;
		this->zAnim = 0;
		this->zAscending = true;
		float amb[4] = {0.4,0.4,0.4,1};
		float dif[4] = {0.5,0.5,0.5,1};
		float spec[4] = {1,1,1,1};
		text = new CGFappearance(amb,dif,spec,20);

		if(this->player==1) {
			temp = new CGFtexture("images-600x331.jpg");
		} else {
			temp = new CGFtexture("images.jpg");
		}
		text->setTexture(temp);
	}

	int getNumberOfPieces() {
		return numberOfPieces;
	}

	int getPlayerNumber() {
		return player;
	}

	void draw(){
		glPushMatrix();
		glTranslated(0.5,+0.5,0);
		for(int i=0;i<this->numberOfPieces;i++){

			if(animated) {
				int xFinal, xInit, yInit, yFinal, numPecasInit;
				xFinal = animStartPoint[0];
				yFinal = animStartPoint[1];
				xInit = animStartPoint[2];
				yInit = animStartPoint[3];
				numPecasInit = animStartPoint[4];

				int deltaX = xInit - xFinal;
				int deltaY = yInit - yFinal;

				if(animType == "exit") {
					if(i == this->numberOfPieces-1) {
						glTranslated(deltaX+xAnim, -(deltaY+yAnim), (0.3*numPecasInit)-0.3+zAnim);
					}
				}
				else if(animType == "move") {
					if(i==0)
						glTranslated(deltaX+xAnim, -(deltaY+yAnim), 0);
				}
				else if(animType == "fusion") {
					//glTranslated(deltaX+xAnim, -(deltaY+yAnim), 0);
				}

			}


			GLUquadric *quadratic = gluNewQuadric();
			gluQuadricTexture(quadratic, true);
			gluCylinder(quadratic, 0.1,0.1, 0.2, 10, 10);

			glTranslated(0, 0, 0.3);

		}
		glPopMatrix();
	}

	void setNumberOfPieces(int pieces){
		this->numberOfPieces=pieces;
	}
	void setPlayer( int player) {
		this->player = player;
	}

	bool getAnimated() {
		return this->animated;
	}

	void setAnimated(bool animated) {
		this->animated = animated;
	}

	const vector<int>& getAnimStartPoint() const {
		return animStartPoint;
	}

	void setAnimStartPoint(const vector<int>& animStartPoint) {
		this->animStartPoint = animStartPoint;
	}

	void update() {
		if(animType == "exit") {
			doExitAnimation();
		}
		else if(animType == "move") {
			doMoveAnimation();
		}
		else if(animType == "fusion") {
			doFusionAnimation();
		}

	}

	void doExitAnimation() {
		if(zAscending) {
			zAnim += (1+(0.3*(3-animStartPoint[4])))/(1000.0/30.0);
			(zAnim >= 1) ? (zAscending = false) : (zAscending = true);
		}
		else {
			zAnim -= (1+(0.3*(3-numberOfPieces)))/(1000.0/30.0);
		}

		int xFinal, xInit, yInit, yFinal, numPecasInit;
		xFinal = animStartPoint[0];
		yFinal = animStartPoint[1];
		xInit = animStartPoint[2];
		yInit = animStartPoint[3];

		float distance = sqrt(pow(xFinal-xInit,2)+pow(yFinal-yInit,2));
		float speed = distance/2.0;
		float toCover = speed/(1000.0/30.0);

		float slope = ((float)yInit-(yFinal+yAnim))/((float)xInit-(xFinal+xAnim));
		cout << "xAnim: " << xAnim << endl;
		cout << "yAnim: " << yAnim << endl;
		cout << slope << endl;

		if(slope < 1) {
			float toCoverY = toCover/2.0;
			float toCoverX = toCover*((sqrt(pow(toCover,2))-pow(toCoverY,2))/toCover);
			if(xFinal > xInit) {
				xAnim += toCoverX;
			}
			else if(xFinal < xInit) {
				xAnim -= toCoverX;
			}

			if(yFinal > yInit) {
				yAnim += toCoverY;
			}
			else if(yFinal < yInit) {
				yAnim -= toCoverY;
			}
		} else if(slope > 1) {
			float toCoverX = toCover/2.0;
			float toCoverY = toCover*((sqrt(pow(toCover,2))-pow(toCoverX,2))/toCover);
			if(xFinal > xInit) {
				xAnim += toCoverX;
			}
			else if(xFinal < xInit) {
				xAnim -= toCoverX;
			}

			if(yFinal > yInit) {
				yAnim += toCoverY;
			}
			else if(yFinal < yInit) {
				yAnim -= toCoverY;
			}
		} else {
			float toCoverBoth = sqrt(pow(toCover,2)/2.0);

			if(xFinal > xInit) {
				xAnim += toCoverBoth;
			}
			else if(xFinal < xInit) {
				xAnim -= toCoverBoth;
			}

			if(yFinal > yInit) {
				yAnim += toCoverBoth;
			}
			else if(yFinal < yInit) {
				yAnim -= toCoverBoth;
			}
		}

		if((zAnim < 0-(0.3*(3-numberOfPieces))) && zAscending == false ) {
			animated = false;
			zAscending = true;
			zAnim = 0;
			xAnim = 0;
			yAnim = 0;
		}
	}

	void doMoveAnimation() {
		int xFinal, xInit, yInit, yFinal, numPecasInit;
		xFinal = animStartPoint[0];
		yFinal = animStartPoint[1];
		xInit = animStartPoint[2];
		yInit = animStartPoint[3];

		float slope = ((float)yInit-(yFinal+yAnim))/((float)xInit-(xFinal+xAnim));

		float xTemp = xInit + xAnim;
		float yTemp = yInit + yAnim;

		if(xInit == xFinal) {
			if(yInit > yFinal) {
				yAnim -= (0.8/(1000.0/30.0));
			}
			else {
				yAnim += (0.8/(1000.0/30.0));
			}
		} else if(yInit == yFinal) {
			if(xInit > xFinal) {
				xAnim -= (0.8/(1000.0/30.0));
			}
			else {
				xAnim += (0.8/(1000.0/30.0));
			}
		}
		cout << "xTEMP" << xTemp << endl;
		cout << "xFinal" << xFinal << endl;
		cout << "yTEMP" << yTemp << endl;
		cout << "yFinal" << yFinal << endl;
		if( abs(xTemp - xFinal) < 0.05 && abs(yTemp - yFinal) < 0.05 ) {
			animated = false;
			xAnim = 0;
			yAnim = 0;
			zAnim = 0;
		}
	}

	void doFusionAnimation() {

	}

	const string& getAnimType() const {
		return animType;
	}

	void setAnimType(const string& animType) {
		this->animType = animType;
	}
};

#endif /* defined(__CGFExample__Stack__) */
