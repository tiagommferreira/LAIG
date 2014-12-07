
#ifndef __CGFExample__Stack__
#define __CGFExample__Stack__

#include <stdio.h>

class Stack {
private:
    int numberOfPieces;
    int player;
    CGFappearance * text;
public:
    Stack(int numberOfPieces, int player){
        this->numberOfPieces=numberOfPieces;
        this->player=player;
        CGFtexture * temp;
        
        float amb[4] = {0.4,0.4,0.4,1};
        float dif[4] = {0.5,0.5,0.5,1};
        float spec[4] = {1,1,1,1};
        text = new CGFappearance(amb,dif,spec,20);

        if(this->player==1) {
            temp = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/images-600x331.jpg");
        } else {
            temp = new CGFtexture("/Users/ricardo/Desktop/CGFlib/CGFexample/data/images.jpg");
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
        text->apply();
        glPushMatrix();
        glTranslated(0.5,+0.5,0);
        for(int i=0;i<this->numberOfPieces;i++){
            GLUquadric *quadratic = gluNewQuadric();
            gluQuadricTexture(quadratic, true);
            gluCylinder(quadratic, 0.1,0.1, 0.2, 10, 10);
            glTranslated(0, 0, 0.3);
        }
        glPopMatrix();
    }
    
};

#endif /* defined(__CGFExample__Stack__) */
