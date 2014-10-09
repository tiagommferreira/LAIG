
#ifndef __CGFExample__Primitive__
#define __CGFExample__Primitive__

#include <stdio.h>

class Primitive {
private:
    float xy1[2], xy2[2]; //rectangle
    float xyz1[3], xyz2[3], xyz3[3]; //triangle
    float base, top, height; //cilinder
    int stacks;
    float inner, outter; //torus
    int loops;
    int slices; //torus and cilinder
    char * value;
    float radius;
    
public:
    void setXY1(char* xy1) {
        sscanf(xy1, "%f %f",&this->xy1[0],&this->xy1[1]);
    }
    void setXY2(char* xy2) {
        sscanf(xy2, "%f %f",&this->xy2[0],&this->xy2[1]);
    }
    void setXYZ1(char* xyz1) {
        sscanf(xyz1, "%f %f %f",&this->xyz1[0],&this->xyz1[1],
               &this->xyz1[2]);
    }
    void setXYZ2(char* xyz2) {
        sscanf(xyz2, "%f %f %f",&this->xyz2[0],&this->xyz2[1],
               &this->xyz2[2]);
    }
    void setXYZ3(char* xyz3) {
        sscanf(xyz3, "%f %f %f",&this->xyz3[0],&this->xyz3[1],
               &this->xyz3[2]);
    }
    void setBase(float base) {this->base = base;}
    void setTop(float top) {this->top = top;}
    void setHeight(float height) {this->height = height;}
    void setInner(float inner) {this->inner = inner;}
    void setOutter(float outter) {this->outter = outter;}
    void setStacks(int stacks) {this->stacks = stacks;}
    void setLoops(int loops) {this->loops = loops;}
    void setSlices(int slices) {this->slices = slices;}
    
    float* getXY1() {return xy1;}
    float* getXY2() {return xy2;}
    float* getXYZ1() {return xyz1;}
    float* getXYZ2() {return xyz2;}
    float* getXYZ3() {return xyz3;}
    
    float getBase() {return base;}
    float getTop() {return top;}
    float getHeight() {return height;}
    float getInner() {return inner;}
    float getOutter() {return outter;}
    
    int getStacks() {return stacks;}
    int getLoops() {return loops;}
    int getStlices() {return slices;}

	char* getValue() const {
		return value;
	}

	void setValue(char* value) {
		this->value = value;
	}

	float getRadius() const {
		return radius;
	}

	void setRadius(float radius) {
		this->radius = radius;
	}
};
#endif /* defined(__CGFExample__Primitive__) */
