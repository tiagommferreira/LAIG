
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
    bool selected;
	CGFappearance * text;
	bool animated, zAscending;
	vector<int> animStartPoint;
	float xAnim, yAnim, zAnim;
	string animType;
	int numPiecesToFuse;
	float dist;
public:
	Stack(int numberOfPieces, int player){
		this->numberOfPieces=numberOfPieces;
        this->selected=false;
		this->player=player;
		CGFtexture * temp;
		this->animated = false;
		this->xAnim = 0;
		this->yAnim = 0;
		this->zAnim = 0;
		this->zAscending = true;
		this->numPiecesToFuse = 0;
		this->dist = 0;
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
    bool getSelected(){
        return selected;
    }
    
    void setSelected(bool value){
        this->selected=value;
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
						glTranslated(deltaX+xAnim, -(deltaY+yAnim), (0.3*numPecasInit)+zAnim);
					}
				}
				else if(animType == "move") {
					if(i==0)
						glTranslated(deltaX+xAnim, -(deltaY+yAnim), 0);
				}
				else if(animType == "fusion") {
					if(i == abs(this->numberOfPieces-this->numPiecesToFuse)) {
						if(numPiecesToFuse == 1)
							glTranslated(deltaX+xAnim, -(deltaY+yAnim), -0.3-(0.3*this->numPiecesToFuse)+zAnim);
						else
							glTranslated(deltaX+xAnim, -(deltaY+yAnim), -0.3+zAnim);
					}

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
			zAnim += (1)/((1000.0/30.0)/2.0);
			(zAnim >= 1) ? (zAscending = false) : (zAscending = true);
		}
		else {
			zAnim -= (1+(0.3*animStartPoint[4])-(0.3*numberOfPieces))/((1000.0/30.0)/2.0);
		}

		int xFinal, xInit, yInit, yFinal, numPecasInit;
		xFinal = animStartPoint[0];
		yFinal = animStartPoint[1];
		xInit = animStartPoint[2];
		yInit = animStartPoint[3];


		float xTemp = xInit + xAnim;
		float yTemp = yInit + yAnim;

		if(xInit == xFinal) {
			if(yInit > yFinal) {
				yAnim -= (0.8/(1000.0/30.0))*2.0;
			}
			else {
				yAnim += (0.8/(1000.0/30.0))*2.0;
			}
		} else if(yInit == yFinal) {
			if(xInit > xFinal) {
				xAnim -= (0.8/(1000.0/30.0))*2.0;
			}
			else {
				xAnim += (0.8/(1000.0/30.0))*2.0;
			}
		}
		else if(xInit > xFinal) {
			float toMoveTotal = sqrt(pow(0.8,2)*2);
			if(yInit > yFinal) {
				if(abs(xInit-xFinal) < 2) { //toda de lado
					float toCoverX = (3.2/(1000.0/30.0))/4.0;
					float toCoverY = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverX,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim -= toCoverY;
					xAnim -= toCoverX;
				}
				else if(abs(yInit-yFinal) < 2) { //toda de lado
					float toCoverY = (3.2/(1000.0/30.0))/4.0;
					float toCoverX = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverY,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim -= toCoverY;
					xAnim -= toCoverX;
				}
				else {
					yAnim -= (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
					xAnim -= (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
				}

			}
			else {
				if(abs(xInit-xFinal) < 2) { //toda de lado
					float toCoverX = (3.2/(1000.0/30.0))/4.0;
					float toCoverY = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverX,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim += toCoverY;
					xAnim -= toCoverX;
				}
				else if(abs(yInit-yFinal) < 2) { //toda de lado
					float toCoverY = (3.2/(1000.0/30.0))/4.0;
					float toCoverX = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverY,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim += toCoverY;
					xAnim -= toCoverX;
				}
				else {
					yAnim += (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
					xAnim -= (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
				}

			}
		}
		else if(xInit < xFinal) {
			float toMoveTotal = sqrt(pow(0.8,2)*2);
			if(yInit > yFinal) {
				if(abs(xInit-xFinal) < 2) { //toda de lado
					cout << "aqui" << endl;
					float toCoverX = (3.2/(1000.0/30.0))/4.0;
					float toCoverY = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverX,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim -= toCoverY;
					xAnim += toCoverX;
				}
				else if(abs(yInit-yFinal) < 2) { //toda de lado
					float toCoverY = (3.2/(1000.0/30.0))/4.0;
					float toCoverX = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverY,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim -= toCoverY;
					xAnim += toCoverX;
				}
				else {
					yAnim -= (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
					xAnim += (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
				}

			}
			else {
				if(abs(xInit-xFinal) < 2) { //toda de lado
					float toCoverX = (3.2/(1000.0/30.0))/4.0;
					float toCoverY = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverX,2))/(3.2/(1000.0/30.0)))/2.0);
					yAnim += toCoverY;
					xAnim += toCoverX;
				}
				else if(abs(yInit-yFinal) < 2) { //toda de lado
					float toCoverY = (3.2/(1000.0/30.0))/4.0;
					float toCoverX = ((3.2/(1000.0/30.0))*((sqrt(pow((3.2/(1000.0/30.0)),2))-pow(toCoverY,2))/(3.2/(1000.0/30.0)))/2.0);

					yAnim += toCoverY;
					xAnim += toCoverX;
				}
				else {
					yAnim += (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
					xAnim += (sqrt((pow(toMoveTotal,2)/2.0)*2.0)/((1000.0/30.0)/1.5));
				}

			}
		}

		if( abs(xTemp - xFinal) < 0.05 && abs(yTemp - yFinal) < 0.05 ) {
			animated = false;
			zAscending = true;
			xAnim = 0;
			yAnim = 0;
			zAnim = 0;
			dist = 0;
		}
	}

	void doMoveAnimation() {
		int xFinal, xInit, yInit, yFinal;
		xFinal = animStartPoint[0];
		yFinal = animStartPoint[1];
		xInit = animStartPoint[2];
		yInit = animStartPoint[3];


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
		else if(xInit > xFinal) {
			float toMoveTotal = sqrt(pow(0.8,2)*2);
			if(yInit > yFinal) {
				yAnim -= (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
				xAnim -= (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
			}
			else {
				yAnim += (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
				xAnim -= (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
			}
		}
		else if(xInit < xFinal) {
			float toMoveTotal = sqrt(pow(0.8,2)*2);
			if(yInit > yFinal) {
				yAnim -= (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
				xAnim += (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
			}
			else {
				yAnim += (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
				xAnim += (sqrt((pow(toMoveTotal,2)/2.0))/(1000.0/30.0));
			}
		}

		if( abs(xTemp - xFinal) < 0.05 && abs(yTemp - yFinal) < 0.05 ) {
			animated = false;
			zAscending = true;
			xAnim = 0;
			yAnim = 0;
			zAnim = 0;
		}
	}

	void doFusionAnimation() {
		if(numPiecesToFuse == 1)
			zAnim += ((0.3*numberOfPieces)-0.3)/(1000.0/30.0);
		else
			zAnim += 0.3/(1000.0/30.0);
		doMoveAnimation();
	}

	const string& getAnimType() const {
		return animType;
	}

	void setAnimType(const string& animType) {
		this->animType = animType;
	}

	int getNumPiecesToFuse() const {
		return numPiecesToFuse;
	}

	void setNumPiecesToFuse(int numPiecesToFuse) {
		this->numPiecesToFuse = numPiecesToFuse;
	}
};

#endif /* defined(__CGFExample__Stack__) */
